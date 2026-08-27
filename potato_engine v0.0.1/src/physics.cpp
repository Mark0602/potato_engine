#include "physics.h"

#include "debug.h"
#include "engine.h"
#include "object.h"
#include "texture.h"

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <unordered_map>
#include <unordered_set>

namespace Physics {
namespace {
constexpr float PI = 3.14159265358979323846f;
constexpr float EPSILON = 0.00001f;
constexpr float CONTACT_WAKE_PADDING = 0.01f;
constexpr std::size_t MAX_GRID_CELLS_PER_BODY = 1024;
using Spatial_Grid_Data = std::unordered_map<std::uint64_t, std::vector<std::size_t>>;

struct Cell_Range {
    int min_x = 0;
    int max_x = 0;
    int min_y = 0;
    int max_y = 0;
    bool valid = false;
    bool too_large = false;
};

struct Body_Pair {
    std::size_t first = 0;
    std::size_t second = 0;
    Collision_Body* body_a = nullptr;
    Collision_Body* body_b = nullptr;

    bool operator==(const Body_Pair& other) const {
        return first == other.first && second == other.second;
    }
};

struct Body_Pair_Hash {
    std::size_t operator()(const Body_Pair& pair) const noexcept {
        const std::size_t first = std::hash<std::size_t>{}(pair.first);
        const std::size_t second = std::hash<std::size_t>{}(pair.second);
        return first ^ (second + 0x9e3779b9U + (first << 6U) + (first >> 2U));
    }
};

struct Body_Step_State {
    Transform transform{};
    Body_Type type = Body_Type::STATIC;
    Collision_Shape shape = Collision_Shape::RECTANGLE;
    bool enabled = false;
    bool is_trigger = false;
    Mask_Tag mask_tag = MASK_DEFAULT;
    Mask_Tag collision_mask = MASK_ALL;
    int active_collision_range = 0;
};

float vec_dot(const Vec& a, const Vec& b) { return a.x * b.x + a.y * b.y; }
float vec_length_squared(const Vec& value) { return vec_dot(value, value); }
float vec_length(const Vec& value) { return std::sqrt(vec_length_squared(value)); }

Vec vec_normalized(const Vec& value) {
    const float magnitude = vec_length(value);
    return magnitude > EPSILON ? value / magnitude : Vec{};
}

Vec rotate_degrees(const Vec& value, float degrees) {
    const float radians = degrees * PI / 180.0f;
    const float c = std::cos(radians);
    const float s = std::sin(radians);
    return {value.x * c - value.y * s, value.x * s + value.y * c};
}

struct Shape_Test_Data {
    const Collision_Body& body;
    Transform transform;
    Vec center;
    float width = 0.0f;
    float height = 0.0f;
    float cosine = 1.0f;
    float sine = 0.0f;
    Texture* texture = nullptr;
};

Shape_Test_Data make_shape_test_data(const Collision_Body& body) {
    const Transform transform = body.collision_transform();
    const float radians = transform.rotation.x * PI / 180.0f;
    return {
        body,
        transform,
        transform.pos + transform.size * 0.5f,
        std::abs(transform.size.x),
        std::abs(transform.size.y),
        std::cos(radians),
        std::sin(radians),
        body.shape() == Collision_Shape::PIXEL_PERFECT ? body.texture() : nullptr
    };
}

Vec world_to_local(const Shape_Test_Data& shape, const Vec& point) {
    const Vec delta = point - shape.center;
    return {
        delta.x * shape.cosine + delta.y * shape.sine + shape.transform.size.x * 0.5f,
        -delta.x * shape.sine + delta.y * shape.cosine + shape.transform.size.y * 0.5f
    };
}

Vec body_center(const Collision_Body& body) {
    const Transform transform = body.collision_transform();
    return transform.pos + transform.size * 0.5f;
}

Vec world_to_local(const Collision_Body& body, const Vec& point) {
    return world_to_local(make_shape_test_data(body), point);
}

AABB transform_bounds(Collision_Shape shape, const Transform& transform) {
    const Vec center = transform.pos + transform.size * 0.5f;
    const Vec half{std::abs(transform.size.x) * 0.5f, std::abs(transform.size.y) * 0.5f};

    if (shape == Collision_Shape::CIRCLE) {
        const float radius = std::min(half.x, half.y);
        return {center - Vec{radius, radius}, center + Vec{radius, radius}};
    }

    const float radians = transform.rotation.x * PI / 180.0f;
    const float c = std::abs(std::cos(radians));
    const float s = std::abs(std::sin(radians));
    const Vec rotated_half{half.x * c + half.y * s, half.x * s + half.y * c};
    return {center - rotated_half, center + rotated_half};
}

AABB body_bounds(const Collision_Body& body) {
    return transform_bounds(body.shape(), body.collision_transform());
}

bool overlaps(const AABB& a, const AABB& b) {
    return a.min.x < b.max.x && a.max.x > b.min.x &&
           a.min.y < b.max.y && a.max.y > b.min.y;
}

bool point_inside(const Shape_Test_Data& shape, const Vec& point) {
    if (shape.width <= EPSILON || shape.height <= EPSILON) return false;

    if (shape.body.shape() == Collision_Shape::CIRCLE) {
        const float radius = std::min(shape.width, shape.height) * 0.5f;
        return vec_length_squared(point - shape.center) <= radius * radius;
    }

    Vec local = world_to_local(shape, point);
    if (local.x < 0.0f || local.y < 0.0f || local.x >= shape.width || local.y >= shape.height) return false;

    if (shape.body.shape() == Collision_Shape::OVAL) {
        const float x = (local.x - shape.width * 0.5f) / (shape.width * 0.5f);
        const float y = (local.y - shape.height * 0.5f) / (shape.height * 0.5f);
        return x * x + y * y <= 1.0f;
    }

    if (shape.body.shape() == Collision_Shape::PIXEL_PERFECT) {
        if (!shape.texture || !shape.texture->has_alpha_mask()) return true; // safe rectangle fallback

        const int flip = static_cast<int>(shape.transform.rotation.y);
        if ((flip & 1) != 0) local.x = shape.width - local.x;
        if ((flip & 2) != 0) local.y = shape.height - local.y;

        const int pixel_x = std::min(static_cast<int>(shape.texture->get_width()) - 1,
            static_cast<int>((local.x / shape.width) * shape.texture->get_width()));
        const int pixel_y = std::min(static_cast<int>(shape.texture->get_height()) - 1,
            static_cast<int>((local.y / shape.height) * shape.texture->get_height()));
        return shape.texture->is_pixel_opaque(pixel_x, pixel_y, shape.body.alpha_threshold());
    }

    return true;
}

int grid_coordinate(float value, float cell_size) {
    const double coordinate = std::floor(static_cast<double>(value) / static_cast<double>(cell_size));
    if (coordinate <= static_cast<double>(std::numeric_limits<int>::min())) {
        return std::numeric_limits<int>::min();
    }
    if (coordinate >= static_cast<double>(std::numeric_limits<int>::max())) {
        return std::numeric_limits<int>::max();
    }
    return static_cast<int>(coordinate);
}

std::uint64_t grid_key(int x, int y) {
    return (static_cast<std::uint64_t>(static_cast<std::uint32_t>(x)) << 32U) |
           static_cast<std::uint32_t>(y);
}

Cell_Range cell_range(const AABB& bounds, float cell_size) {
    Cell_Range range;
    if (!std::isfinite(bounds.min.x) || !std::isfinite(bounds.min.y) ||
        !std::isfinite(bounds.max.x) || !std::isfinite(bounds.max.y)) {
        return range;
    }

    range.min_x = grid_coordinate(bounds.min.x, cell_size);
    range.max_x = grid_coordinate(bounds.max.x, cell_size);
    range.min_y = grid_coordinate(bounds.min.y, cell_size);
    range.max_y = grid_coordinate(bounds.max.y, cell_size);
    const std::uint64_t columns = static_cast<std::uint64_t>(
        static_cast<std::int64_t>(range.max_x) - static_cast<std::int64_t>(range.min_x) + 1
    );
    const std::uint64_t rows = static_cast<std::uint64_t>(
        static_cast<std::int64_t>(range.max_y) - static_cast<std::int64_t>(range.min_y) + 1
    );
    range.valid = columns > 0 && rows > 0;
    range.too_large = range.valid &&
        (columns > MAX_GRID_CELLS_PER_BODY ||
         rows > MAX_GRID_CELLS_PER_BODY ||
         columns * rows > MAX_GRID_CELLS_PER_BODY);
    return range;
}

void insert_spatial_body(
    Spatial_Grid_Data& grid,
    std::vector<std::size_t>& large_bodies,
    std::size_t body_index,
    const AABB& bounds,
    float cell_size
) {
    const Cell_Range range = cell_range(bounds, cell_size);
    if (!range.valid) return;
    if (range.too_large) {
        large_bodies.push_back(body_index);
        return;
    }

    for (std::int64_t y = range.min_y; y <= static_cast<std::int64_t>(range.max_y); ++y) {
        for (std::int64_t x = range.min_x; x <= static_cast<std::int64_t>(range.max_x); ++x) {
            grid[grid_key(static_cast<int>(x), static_cast<int>(y))].push_back(body_index);
        }
    }
}

template <typename Visitor>
void visit_spatial_bodies(
    const Spatial_Grid_Data& grid,
    const AABB& bounds,
    float cell_size,
    Visitor&& visitor
) {
    const Cell_Range range = cell_range(bounds, cell_size);
    if (!range.valid || range.too_large) return;

    for (std::int64_t y = range.min_y; y <= static_cast<std::int64_t>(range.max_y); ++y) {
        for (std::int64_t x = range.min_x; x <= static_cast<std::int64_t>(range.max_x); ++x) {
            const auto bucket = grid.find(grid_key(static_cast<int>(x), static_cast<int>(y)));
            if (bucket == grid.end()) continue;
            for (std::size_t index : bucket->second) visitor(index);
        }
    }
}

AABB merged_bounds(const AABB& a, const AABB& b, float padding) {
    const Vec expansion{padding, padding};
    return {
        Vec{std::min(a.min.x, b.min.x), std::min(a.min.y, b.min.y)} - expansion,
        Vec{std::max(a.max.x, b.max.x), std::max(a.max.y, b.max.y)} + expansion
    };
}

bool transforms_equal(const Transform& a, const Transform& b) {
    constexpr float tolerance = 0.0001f;
    const auto close = [&](float left, float right) {
        return std::abs(left - right) <= tolerance;
    };
    return close(a.pos.x, b.pos.x) && close(a.pos.y, b.pos.y) &&
           close(a.size.x, b.size.x) && close(a.size.y, b.size.y) &&
           close(a.rotation.x, b.rotation.x) && close(a.rotation.y, b.rotation.y);
}

Collision bounds_manifold(Collision_Body& a, Collision_Body& b, const AABB& aa, const AABB& bb) {
    Collision result;
    result.body_a = &a;
    result.body_b = &b;
    const float overlap_x = std::min(aa.max.x, bb.max.x) - std::max(aa.min.x, bb.min.x);
    const float overlap_y = std::min(aa.max.y, bb.max.y) - std::max(aa.min.y, bb.min.y);
    const Vec delta = body_center(b) - body_center(a);
    if (overlap_x < overlap_y) {
        result.penetration = overlap_x;
        result.normal = {delta.x < 0.0f ? -1.0f : 1.0f, 0.0f};
    } else {
        result.penetration = overlap_y;
        result.normal = {0.0f, delta.y < 0.0f ? -1.0f : 1.0f};
    }
    result.point = {
        (std::max(aa.min.x, bb.min.x) + std::min(aa.max.x, bb.max.x)) * 0.5f,
        (std::max(aa.min.y, bb.min.y) + std::min(aa.max.y, bb.max.y)) * 0.5f
    };
    return result;
}

bool circle_circle(Collision_Body& a, Collision_Body& b, Collision& result) {
    const Vec center_a = body_center(a);
    const Vec center_b = body_center(b);
    const Transform ta = a.collision_transform();
    const Transform tb = b.collision_transform();
    const float radius_a = std::min(std::abs(ta.size.x), std::abs(ta.size.y)) * 0.5f;
    const float radius_b = std::min(std::abs(tb.size.x), std::abs(tb.size.y)) * 0.5f;
    const Vec delta = center_b - center_a;
    const float distance = vec_length(delta);
    const float combined = radius_a + radius_b;
    if (distance >= combined) return false;
    result.body_a = &a;
    result.body_b = &b;
    result.normal = distance > EPSILON ? delta / distance : Vec{1.0f, 0.0f};
    result.penetration = combined - distance;
    result.point = center_a + result.normal * (radius_a - result.penetration * 0.5f);
    return true;
}

bool circle_rectangle(
    Collision_Body& circle,
    Collision_Body& rectangle,
    const AABB& rect,
    Collision& result
) {
    const Vec center = body_center(circle);
    const Transform transform = circle.collision_transform();
    const float radius = std::min(std::abs(transform.size.x), std::abs(transform.size.y)) * 0.5f;
    const Vec closest{
        std::clamp(center.x, rect.min.x, rect.max.x),
        std::clamp(center.y, rect.min.y, rect.max.y)
    };
    Vec delta = closest - center; // circle -> rectangle
    float distance = vec_length(delta);
    if (distance >= radius) return false;
    if (distance <= EPSILON) {
        const float edge_distances[] = {
            center.x - rect.min.x, rect.max.x - center.x,
            center.y - rect.min.y, rect.max.y - center.y
        };
        int nearest_edge = 0;
        for (int i = 1; i < 4; ++i) {
            if (edge_distances[i] < edge_distances[nearest_edge]) nearest_edge = i;
        }

        result.normal = nearest_edge == 0 ? Vec{1.0f, 0.0f} : nearest_edge == 1 ? Vec{-1.0f, 0.0f} :
                        nearest_edge == 2 ? Vec{0.0f, 1.0f} : Vec{0.0f, -1.0f};
        result.penetration = radius + edge_distances[nearest_edge];
        result.point = center - result.normal * edge_distances[nearest_edge];
    } else {
        result.normal = delta / distance;
        result.penetration = radius - distance;
        result.point = closest;
    }
    result.body_a = &circle;
    result.body_b = &rectangle;
    return true;
}

bool sampled_collision(Collision_Body& a, Collision_Body& b, const AABB& aa, const AABB& bb, Collision& result) {
    const float min_x = std::max(aa.min.x, bb.min.x);
    const float max_x = std::min(aa.max.x, bb.max.x);
    const float min_y = std::max(aa.min.y, bb.min.y);
    const float max_y = std::min(aa.max.y, bb.max.y);
    const Shape_Test_Data shape_a = make_shape_test_data(a);
    const Shape_Test_Data shape_b = make_shape_test_data(b);

    for (float y = std::floor(min_y); y < std::ceil(max_y); y += 1.0f) {
        for (float x = std::floor(min_x); x < std::ceil(max_x); x += 1.0f) {
            const Vec sample{x + 0.5f, y + 0.5f};
            if (point_inside(shape_a, sample) && point_inside(shape_b, sample)) {
                result = bounds_manifold(a, b, aa, bb);
                result.point = sample;
                return true;
            }
        }
    }

    const Vec samples[] = {
        {(min_x + max_x) * 0.5f, (min_y + max_y) * 0.5f},
        {min_x, min_y}, {max_x, min_y}, {min_x, max_y}, {max_x, max_y}
    };
    for (const Vec& sample : samples) {
        if (point_inside(shape_a, sample) && point_inside(shape_b, sample)) {
            result = bounds_manifold(a, b, aa, bb);
            result.point = sample;
            return true;
        }
    }
    return false;
}

bool test_collision_with_bounds(
    Collision_Body& a,
    Collision_Body& b,
    const AABB& aa,
    const AABB& bb,
    Collision* output
) {
    if (!a.enabled || !b.enabled || !overlaps(aa, bb)) return false;

    Collision result;
    bool hit = false;
    const bool a_axis_rect = a.shape() == Collision_Shape::RECTANGLE &&
                             std::abs(a.collision_transform().rotation.x) <= EPSILON;
    const bool b_axis_rect = b.shape() == Collision_Shape::RECTANGLE &&
                             std::abs(b.collision_transform().rotation.x) <= EPSILON;
    if (a_axis_rect && b_axis_rect) {
        result = bounds_manifold(a, b, aa, bb);
        hit = true;
    } else if (a.shape() == Collision_Shape::CIRCLE && b.shape() == Collision_Shape::CIRCLE) {
        hit = circle_circle(a, b, result);
    } else if (a.shape() == Collision_Shape::CIRCLE && b_axis_rect) {
        hit = circle_rectangle(a, b, bb, result);
    } else if (b.shape() == Collision_Shape::CIRCLE && a_axis_rect) {
        hit = circle_rectangle(b, a, aa, result);
        std::swap(result.body_a, result.body_b);
        result.normal *= -1.0f;
    } else {
        hit = sampled_collision(a, b, aa, bb, result);
    }

    if (hit && output) *output = result;
    return hit;
}

Vec surface_normal(const Collision_Body& body, const Vec& point, const Vec& ray_direction) {
    if (body.shape() == Collision_Shape::CIRCLE) return vec_normalized(point - body_center(body));
    if (body.shape() == Collision_Shape::OVAL) {
        const Transform transform = body.collision_transform();
        const Vec local = world_to_local(body, point);
        const float rx = std::max(std::abs(transform.size.x) * 0.5f, EPSILON);
        const float ry = std::max(std::abs(transform.size.y) * 0.5f, EPSILON);
        const Vec gradient{(local.x - rx) / (rx * rx), (local.y - ry) / (ry * ry)};
        return vec_normalized(rotate_degrees(gradient, transform.rotation.x));
    }
    if (body.shape() == Collision_Shape::PIXEL_PERFECT) return vec_normalized(ray_direction) * -1.0f;

    const Transform transform = body.collision_transform();
    const Vec local = world_to_local(body, point);
    const float width = std::abs(transform.size.x);
    const float height = std::abs(transform.size.y);
    const float distances[] = {local.x, width - local.x, local.y, height - local.y};
    int nearest = 0;
    for (int i = 1; i < 4; ++i) {
        if (distances[i] < distances[nearest]) nearest = i;
    }

    Vec normal = nearest == 0 ? Vec{-1.0f, 0.0f} : nearest == 1 ? Vec{1.0f, 0.0f} :
                 nearest == 2 ? Vec{0.0f, -1.0f} : Vec{0.0f, 1.0f};
    return rotate_degrees(normal, transform.rotation.x);
}

bool ray_box_interval(
    const Vec& origin,
    const Vec& direction,
    const Vec& minimum,
    const Vec& maximum,
    float max_distance,
    float& entry,
    float& exit
) {
    entry = 0.0f;
    exit = max_distance;

    const auto test_axis = [&](float ray_origin, float ray_direction, float min_value, float max_value) {
        if (std::abs(ray_direction) <= EPSILON) {
            return ray_origin >= min_value && ray_origin <= max_value;
        }

        float near_distance = (min_value - ray_origin) / ray_direction;
        float far_distance = (max_value - ray_origin) / ray_direction;
        if (near_distance > far_distance) std::swap(near_distance, far_distance);
        entry = std::max(entry, near_distance);
        exit = std::min(exit, far_distance);
        return entry <= exit;
    };

    return test_axis(origin.x, direction.x, minimum.x, maximum.x) &&
           test_axis(origin.y, direction.y, minimum.y, maximum.y) &&
           exit >= 0.0f && entry <= max_distance;
}

bool ray_shape_distance(
    const Collision_Body& body,
    const Vec& origin,
    const Vec& direction,
    float max_distance,
    float& distance
) {
    const Shape_Test_Data shape = make_shape_test_data(body);
    if (shape.width <= EPSILON || shape.height <= EPSILON) return false;
    if (point_inside(shape, origin)) {
        distance = 0.0f;
        return true;
    }

    if (body.shape() == Collision_Shape::CIRCLE) {
        const float radius = std::min(shape.width, shape.height) * 0.5f;
        const Vec offset = origin - shape.center;
        const float projected = vec_dot(offset, direction);
        const float discriminant = projected * projected -
                                   (vec_length_squared(offset) - radius * radius);
        if (discriminant < 0.0f) return false;
        const float hit_distance = -projected - std::sqrt(discriminant);
        if (hit_distance < 0.0f || hit_distance > max_distance) return false;
        distance = hit_distance;
        return true;
    }

    const Vec local_origin = world_to_local(shape, origin);
    const Vec local_direction{
        direction.x * shape.cosine + direction.y * shape.sine,
        -direction.x * shape.sine + direction.y * shape.cosine
    };

    if (body.shape() == Collision_Shape::OVAL) {
        const float radius_x = shape.width * 0.5f;
        const float radius_y = shape.height * 0.5f;
        const Vec normalized_origin{
            (local_origin.x - radius_x) / radius_x,
            (local_origin.y - radius_y) / radius_y
        };
        const Vec normalized_direction{
            local_direction.x / radius_x,
            local_direction.y / radius_y
        };
        const float a = vec_length_squared(normalized_direction);
        const float b = vec_dot(normalized_origin, normalized_direction);
        const float c = vec_length_squared(normalized_origin) - 1.0f;
        const float discriminant = b * b - a * c;
        if (a <= EPSILON || discriminant < 0.0f) return false;
        const float hit_distance = (-b - std::sqrt(discriminant)) / a;
        if (hit_distance < 0.0f || hit_distance > max_distance) return false;
        distance = hit_distance;
        return true;
    }

    float entry = 0.0f;
    float exit = max_distance;
    if (!ray_box_interval(
            local_origin,
            local_direction,
            {0.0f, 0.0f},
            {shape.width, shape.height},
            max_distance,
            entry,
            exit)) {
        return false;
    }

    if (body.shape() == Collision_Shape::RECTANGLE ||
        !shape.texture || !shape.texture->has_alpha_mask()) {
        distance = std::max(0.0f, entry);
        return true;
    }

    // Pixel masks still need sampling, but only across this body's intersected
    // interval instead of walking the whole ray against every registered body.
    constexpr float sample_step = 0.5f;
    float sample_distance = std::max(0.0f, entry);
    if (sample_distance > 0.0f) sample_distance += EPSILON;
    for (; sample_distance <= exit; sample_distance += sample_step) {
        if (point_inside(shape, origin + direction * sample_distance)) {
            distance = sample_distance;
            return true;
        }
    }

    const float final_distance = std::max(0.0f, exit - EPSILON);
    if (final_distance <= max_distance &&
        point_inside(shape, origin + direction * final_distance)) {
        distance = final_distance;
        return true;
    }
    return false;
}
} // namespace

Collision_Body::Collision_Body(Object* owner, Collision_Shape shape, Body_Type type)
    : m_owner(owner), m_shape(shape), m_type(type) {
    if (Engine::physics_engine) Engine::physics_engine->add_body(this);
}

Collision_Body::Collision_Body(const Transform& transform, Collision_Shape shape, Body_Type type)
    : m_standalone_transform(transform), m_shape(shape), m_type(type) {
    if (Engine::physics_engine) Engine::physics_engine->add_body(this);
}

Collision_Body::~Collision_Body() {
    if (m_world) m_world->remove_body(this);
}

Transform& Collision_Body::transform() {
    return m_owner ? m_owner->transform : m_standalone_transform;
}

const Transform& Collision_Body::transform() const {
    return m_owner ? m_owner->transform : m_standalone_transform;
}

Transform Collision_Body::collision_transform() const {
    Transform result = transform();
    if (m_use_local_bounds) {
        result.pos += m_local_transform.pos;
        result.size = m_local_transform.size;
        result.rotation += m_local_transform.rotation;
    }
    return result;
}

void Collision_Body::set_local_transform(const Transform& transform) {
    m_local_transform = transform;
    m_use_local_bounds = true;
    wake();
    if (m_world && m_type == Body_Type::STATIC) m_world->m_static_grid_dirty = true;
}

void Collision_Body::set_local_bounds(Vec offset, Vec size) {
    set_local_transform(Transform(offset, size));
}

void Collision_Body::clear_local_bounds() {
    if (!m_use_local_bounds) return;
    m_use_local_bounds = false;
    wake();
    if (m_world && m_type == Body_Type::STATIC) m_world->m_static_grid_dirty = true;
}

void Collision_Body::set_shape(Collision_Shape shape) {
    if (m_shape == shape) return;
    m_shape = shape;
    wake();
    if (m_world && m_type == Body_Type::STATIC) m_world->m_static_grid_dirty = true;
}

void Collision_Body::set_body_type(Body_Type type) {
    if (m_type == type) return;
    m_type = type;
    wake();
    if (m_world) m_world->m_static_grid_dirty = true;
}

Texture* Collision_Body::texture() const {
    return m_pixel_texture ? m_pixel_texture : (m_owner ? m_owner->texture : nullptr);
}

void Collision_Body::set_mass(float mass) {
    m_mass = std::max(mass, EPSILON);
}

float Collision_Body::inverse_mass() const {
    return m_type == Body_Type::DYNAMIC ? 1.0f / m_mass : 0.0f;
}

void Collision_Body::apply_force(const Vec& force) {
    if (m_type != Body_Type::DYNAMIC) return;
    m_force += force;
    if (vec_length_squared(force) > EPSILON * EPSILON) wake();
}

void Collision_Body::apply_impulse(const Vec& impulse) {
    if (m_type == Body_Type::DYNAMIC) {
        velocity += impulse * inverse_mass();
        if (vec_length_squared(impulse) > EPSILON * EPSILON) wake();
    }
}

void Collision_Body::wake() {
    if (m_type == Body_Type::STATIC) return;
    awake = true;
    m_stationary_steps = 0;
}

void Collision_Body::sleep() {
    if (m_type == Body_Type::STATIC) return;
    awake = false;
    velocity = {};
    m_force = {};
    m_stationary_steps = 0;
}

Gravitational_Object::Gravitational_Object(Object* owner, Collision_Shape shape, float mass)
    : Collision_Body(owner, shape, Body_Type::DYNAMIC) {
    set_mass(mass);
    gravity_scale = 1.0f;
}

Gravitational_Object::Gravitational_Object(const Transform& transform, Collision_Shape shape, float mass)
    : Collision_Body(transform, shape, Body_Type::DYNAMIC) {
    set_mass(mass);
    gravity_scale = 1.0f;
}

Physics_Engine::~Physics_Engine() { clear(); }

void Physics_Engine::add_body(Collision_Body* body) {
    if (!body) return;

    if (body->m_world && body->m_world != this) body->m_world->remove_body(body);
    if (std::find(m_bodies.begin(), m_bodies.end(), body) == m_bodies.end()) {
        m_bodies.push_back(body);
        body->m_world = this;
        body->m_previous_transform = body->collision_transform();
        body->m_previous_type = body->m_type;
        body->m_previous_shape = body->m_shape;
        body->m_previous_enabled = body->enabled;
        body->m_previous_is_trigger = body->is_trigger;
        body->m_previous_mask_tag = body->mask_tag;
        body->m_previous_collision_mask = body->collision_mask;
        body->m_previous_active_collision_range = body->active_collision_range;
        // The first step must still treat a newly registered body as active.
        // This lets a new static collider wake and resolve nearby sleepers.
        body->m_tracking_initialized = false;
        m_static_grid_dirty = true;
    }
}

void Physics_Engine::remove_body(Collision_Body* body) {
    if (!body) return;
    if (body->enabled) {
        const float padding = CONTACT_WAKE_PADDING +
            static_cast<float>(std::max(0, body->active_collision_range));
        const AABB bounds = body_bounds(*body);
        const AABB affected_bounds = merged_bounds(bounds, bounds, padding);
        for (Collision_Body* candidate : m_bodies) {
            if (!candidate || candidate == body || !candidate->enabled ||
                candidate->m_type == Body_Type::STATIC) {
                continue;
            }
            if (overlaps(affected_bounds, body_bounds(*candidate))) candidate->wake();
        }
    }
    m_bodies.erase(std::remove(m_bodies.begin(), m_bodies.end(), body), m_bodies.end());
    if (body->m_world == this) body->m_world = nullptr;
    m_static_grid_dirty = true;
}

void Physics_Engine::clear() {
    for (Collision_Body* body : m_bodies) {
        if (body && body->m_world == this) body->m_world = nullptr;
    }
    m_bodies.clear();
    m_collisions.clear();
    m_static_grid.clear();
    m_large_static_bodies.clear();
    m_static_grid_dirty = true;
    m_accumulator = 0.0f;
}

void Physics_Engine::set_fixed_timestep(float seconds) {
    if (seconds > EPSILON) m_fixed_timestep = seconds;
}

void Physics_Engine::set_max_substeps(int count) {
    m_max_substeps = std::max(1, count);
}

void Physics_Engine::set_spatial_cell_size(float size) {
    if (size > EPSILON && std::isfinite(size) && std::abs(size - m_spatial_cell_size) > EPSILON) {
        m_spatial_cell_size = size;
        m_static_grid_dirty = true;
    }
}

void Physics_Engine::set_sleep_settings(float velocity_threshold, int stationary_steps) {
    if (velocity_threshold >= 0.0f && std::isfinite(velocity_threshold)) {
        m_sleep_velocity_threshold = velocity_threshold;
    }
    m_sleep_after_steps = std::max(1, stationary_steps);
}

void Physics_Engine::rebuild_static_grid() {
    m_static_grid.clear();
    m_large_static_bodies.clear();
    m_static_grid.reserve(m_bodies.size() * 2U + 1U);

    for (std::size_t index = 0; index < m_bodies.size(); ++index) {
        Collision_Body* body = m_bodies[index];
        if (!body || !body->enabled || body->m_type != Body_Type::STATIC) continue;
        insert_spatial_body(
            m_static_grid,
            m_large_static_bodies,
            index,
            body_bounds(*body),
            m_spatial_cell_size
        );
    }
    m_static_grid_dirty = false;
}

void Physics_Engine::update(float delta_seconds) {
    if (delta_seconds <= 0.0f) return;
    m_accumulator += std::min(delta_seconds, m_fixed_timestep * static_cast<float>(m_max_substeps));
    int steps = 0;
    while (m_accumulator >= m_fixed_timestep && steps < m_max_substeps) {
        step(m_fixed_timestep);
        m_accumulator -= m_fixed_timestep;
        ++steps;
    }
}

bool Physics_Engine::masks_allow(const Collision_Body& a, const Collision_Body& b) {
    return (a.collision_mask & b.mask_tag) != 0 && (b.collision_mask & a.mask_tag) != 0;
}

void Physics_Engine::step(float delta_seconds) {
    if (delta_seconds <= 0.0f) return;
    m_collisions.clear();

    const std::size_t body_count = m_bodies.size();
    std::vector<bool> active(body_count, false);
    std::vector<AABB> start_bounds(body_count);
    std::vector<AABB> search_bounds(body_count);
    std::vector<Body_Step_State> step_start_states(body_count);
    std::vector<AABB> changed_collider_bounds;
    changed_collider_bounds.reserve(4);
    std::size_t active_count = 0;
    const float wake_velocity_squared = m_sleep_velocity_threshold * m_sleep_velocity_threshold;

    for (std::size_t index = 0; index < body_count; ++index) {
        Collision_Body* body = m_bodies[index];
        if (!body) continue;

        const Transform current_transform = body->collision_transform();
        step_start_states[index] = {
            current_transform,
            body->m_type,
            body->m_shape,
            body->enabled,
            body->is_trigger,
            body->mask_tag,
            body->collision_mask,
            body->active_collision_range
        };

        const bool newly_registered = !body->m_tracking_initialized;
        if (newly_registered) {
            body->m_previous_transform = current_transform;
            body->m_previous_type = body->m_type;
            body->m_previous_shape = body->m_shape;
            body->m_previous_enabled = body->enabled;
            body->m_previous_is_trigger = body->is_trigger;
            body->m_previous_mask_tag = body->mask_tag;
            body->m_previous_collision_mask = body->collision_mask;
            body->m_previous_active_collision_range = body->active_collision_range;
            body->m_tracking_initialized = true;
        }

        const bool transform_changed =
            !transforms_equal(current_transform, body->m_previous_transform);
        const bool grid_membership_changed =
            newly_registered || body->m_type != body->m_previous_type ||
            body->m_shape != body->m_previous_shape ||
            body->enabled != body->m_previous_enabled;
        const bool classification_changed =
            grid_membership_changed ||
            body->is_trigger != body->m_previous_is_trigger ||
            body->mask_tag != body->m_previous_mask_tag ||
            body->collision_mask != body->m_previous_collision_mask ||
            body->active_collision_range != body->m_previous_active_collision_range;
        if ((transform_changed || classification_changed) &&
            (body->enabled || body->m_previous_enabled)) {
            const AABB previous_bounds = transform_bounds(
                body->m_previous_shape, body->m_previous_transform
            );
            const AABB current_bounds = transform_bounds(body->m_shape, current_transform);
            changed_collider_bounds.push_back(merged_bounds(
                previous_bounds,
                current_bounds,
                CONTACT_WAKE_PADDING +
                    static_cast<float>(std::max(0, body->active_collision_range))
            ));
        }
        if ((body->m_type == Body_Type::STATIC || body->m_previous_type == Body_Type::STATIC) &&
            (transform_changed || grid_membership_changed)) {
            m_static_grid_dirty = true;
        }
        if (!body->enabled) continue;

        const AABB current_start_bounds = body_bounds(*body);
        start_bounds[index] = transform_changed
            ? transform_bounds(body->m_previous_shape, body->m_previous_transform)
            : current_start_bounds;
        if (body->m_type == Body_Type::STATIC) {
            // Static triggers keep their previous per-step callback semantics.
            active[index] = transform_changed || classification_changed || body->is_trigger;
            search_bounds[index] = merged_bounds(
                start_bounds[index], current_start_bounds,
                static_cast<float>(std::max(0, body->active_collision_range))
            );
        } else {
            const bool externally_activated = transform_changed || classification_changed ||
                vec_length_squared(body->velocity) > wake_velocity_squared ||
                vec_length_squared(body->m_force) > EPSILON * EPSILON;
            if (externally_activated || !m_auto_sleep) body->wake();
            active[index] = body->awake;

            if (active[index]) {
                if (body->m_type == Body_Type::DYNAMIC) {
                    const Vec acceleration = body->m_force * body->inverse_mass() +
                                             m_gravity * body->gravity_scale;
                    body->velocity += acceleration * delta_seconds;
                    body->velocity *= std::max(
                        0.0f, 1.0f - body->linear_damping * delta_seconds
                    );
                    body->m_force = {};
                }
                body->transform().pos += body->velocity * delta_seconds;
            }

            const AABB end_bounds = body_bounds(*body);
            search_bounds[index] = merged_bounds(
                start_bounds[index], end_bounds,
                static_cast<float>(std::max(0, body->active_collision_range))
            );
        }

        if (active[index]) ++active_count;
    }

    if (m_static_grid_dirty) rebuild_static_grid();

    Spatial_Grid_Data dynamic_grid;
    std::vector<std::size_t> large_dynamic_bodies;
    dynamic_grid.reserve(body_count + 1U);
    for (std::size_t index = 0; index < body_count; ++index) {
        Collision_Body* body = m_bodies[index];
        if (!body || !body->enabled || body->m_type == Body_Type::STATIC) continue;
        insert_spatial_body(
            dynamic_grid,
            large_dynamic_bodies,
            index,
            body_bounds(*body),
            m_spatial_cell_size
        );
    }

    const auto wake_near_collider_change = [&](std::size_t target, const AABB& affected_bounds) {
        if (target >= body_count) return;
        Collision_Body* body = m_bodies[target];
        if (!body || !body->enabled || body->m_type == Body_Type::STATIC ||
            !overlaps(affected_bounds, body_bounds(*body))) {
            return;
        }
        if (!active[target]) {
            body->wake();
            active[target] = true;
            ++active_count;
        }
    };
    for (const AABB& affected_bounds : changed_collider_bounds) {
        const Cell_Range affected_range = cell_range(affected_bounds, m_spatial_cell_size);
        if (affected_range.too_large) {
            for (std::size_t target = 0; target < body_count; ++target) {
                wake_near_collider_change(target, affected_bounds);
            }
        } else {
            visit_spatial_bodies(
                dynamic_grid, affected_bounds, m_spatial_cell_size,
                [&](std::size_t target) { wake_near_collider_change(target, affected_bounds); }
            );
            for (std::size_t target : large_dynamic_bodies) {
                wake_near_collider_change(target, affected_bounds);
            }
        }
    }

    std::vector<Body_Pair> candidate_pairs;
    std::unordered_set<Body_Pair, Body_Pair_Hash> seen_pairs;
    seen_pairs.reserve(active_count * 8U + 1U);

    const auto add_pair = [&](std::size_t a, std::size_t b) {
        if (a == b || a >= body_count || b >= body_count) return;
        const std::size_t first = std::min(a, b);
        const std::size_t second = std::max(a, b);
        Collision_Body* body_a = m_bodies[first];
        Collision_Body* body_b = m_bodies[second];
        if (!body_a || !body_b || !body_a->enabled || !body_b->enabled ||
            !masks_allow(*body_a, *body_b)) {
            return;
        }
        if (body_a->m_type == Body_Type::STATIC && body_b->m_type == Body_Type::STATIC &&
            !body_a->is_trigger && !body_b->is_trigger) {
            return;
        }
        Body_Pair pair{first, second, body_a, body_b};
        if (seen_pairs.insert(pair).second) candidate_pairs.push_back(pair);
    };

    const auto consider_nearby_body = [&](std::size_t source, std::size_t target) {
        if (source >= body_count || target >= body_count || source == target) return;
        Collision_Body* source_body = m_bodies[source];
        Collision_Body* target_body = m_bodies[target];
        if (!source_body || !target_body || !source_body->enabled || !target_body->enabled ||
            !masks_allow(*source_body, *target_body)) {
            return;
        }
        // A moving collider that leaves a sleeping support/contact must wake it
        // even when the two final transforms no longer overlap.
        if (!source_body->is_trigger && target_body->m_type != Body_Type::STATIC &&
            !target_body->awake && overlaps(search_bounds[source], body_bounds(*target_body))) {
            target_body->wake();
            active[target] = true;
        }
        add_pair(source, target);
    };

    for (std::size_t source = 0; source < body_count; ++source) {
        if (!active[source] || !m_bodies[source] || !m_bodies[source]->enabled) continue;
        const Cell_Range range = cell_range(search_bounds[source], m_spatial_cell_size);
        if (!range.valid) continue;

        if (range.too_large) {
            for (std::size_t target = 0; target < body_count; ++target) {
                consider_nearby_body(source, target);
            }
            continue;
        }

        visit_spatial_bodies(
            m_static_grid, search_bounds[source], m_spatial_cell_size,
            [&](std::size_t target) { consider_nearby_body(source, target); }
        );
        visit_spatial_bodies(
            dynamic_grid, search_bounds[source], m_spatial_cell_size,
            [&](std::size_t target) { consider_nearby_body(source, target); }
        );
        for (std::size_t target : m_large_static_bodies) {
            consider_nearby_body(source, target);
        }
        for (std::size_t target : large_dynamic_bodies) {
            consider_nearby_body(source, target);
        }
    }

    std::sort(candidate_pairs.begin(), candidate_pairs.end(), [](const Body_Pair& a, const Body_Pair& b) {
        return a.first < b.first || (a.first == b.first && a.second < b.second);
    });

    // Narrow phase and resolution intentionally remain deterministic. Resolving
    // two contacts may modify the same body, and gameplay callbacks may mutate
    // arbitrary engine state, so parallel execution would introduce data races.
    for (const Body_Pair& pair : candidate_pairs) {
        Collision_Body* a = pair.body_a;
        Collision_Body* b = pair.body_b;
        if (!a || !b || !a->enabled || !b->enabled || !masks_allow(*a, *b)) continue;
        if (a->m_type == Body_Type::STATIC && b->m_type == Body_Type::STATIC &&
            !a->is_trigger && !b->is_trigger) {
            continue;
        }

        Collision collision;
        if (!test_collision(*a, *b, &collision)) continue;
        m_collisions.push_back(collision);
        Collision& stored_collision = m_collisions.back();
        if (!a->is_trigger && !b->is_trigger) {
            if (a->m_type != Body_Type::STATIC && !a->awake && active[pair.second]) a->wake();
            if (b->m_type != Body_Type::STATIC && !b->awake && active[pair.first]) b->wake();
            resolve(stored_collision);
        }

        if (a->m_callback) a->m_callback(stored_collision);
        if (b->m_callback) {
            Collision reversed = stored_collision;
            std::swap(reversed.body_a, reversed.body_b);
            reversed.normal *= -1.0f;
            b->m_callback(reversed);
        }
    }

    const float sleep_velocity_squared =
        m_sleep_velocity_threshold * m_sleep_velocity_threshold;
    const std::size_t final_body_count = m_bodies.size();
    for (std::size_t index = 0; index < final_body_count; ++index) {
        Collision_Body* body = m_bodies[index];
        if (!body) continue;

        if (body->enabled && body->m_type != Body_Type::STATIC && body->awake && m_auto_sleep) {
            if (vec_length_squared(body->velocity) <= sleep_velocity_squared &&
                vec_length_squared(body->m_force) <= EPSILON * EPSILON) {
                ++body->m_stationary_steps;
                if (body->m_stationary_steps >= m_sleep_after_steps) body->sleep();
            } else {
                body->m_stationary_steps = 0;
            }
        } else if (!m_auto_sleep) {
            body->m_stationary_steps = 0;
        }

        const Transform final_transform = body->collision_transform();
        bool preserve_step_start_state = false;
        if (index < body_count) {
            const Body_Step_State& step_start = step_start_states[index];
            if (step_start.type == Body_Type::STATIC || body->m_type == Body_Type::STATIC) {
                const bool geometry_changed_during_step =
                    !transforms_equal(final_transform, step_start.transform) ||
                    body->m_type != step_start.type ||
                    body->m_shape != step_start.shape ||
                    body->enabled != step_start.enabled;
                preserve_step_start_state = geometry_changed_during_step ||
                    body->is_trigger != step_start.is_trigger ||
                    body->mask_tag != step_start.mask_tag ||
                    body->collision_mask != step_start.collision_mask ||
                    body->active_collision_range != step_start.active_collision_range;
                if (geometry_changed_during_step) m_static_grid_dirty = true;
            }
        }
        if (preserve_step_start_state) {
            // A callback mutated a static collider after broad phase. Keep the
            // pre-step snapshot once so the next step activates its old/new area.
            const Body_Step_State& step_start = step_start_states[index];
            body->m_previous_transform = step_start.transform;
            body->m_previous_type = step_start.type;
            body->m_previous_shape = step_start.shape;
            body->m_previous_enabled = step_start.enabled;
            body->m_previous_is_trigger = step_start.is_trigger;
            body->m_previous_mask_tag = step_start.mask_tag;
            body->m_previous_collision_mask = step_start.collision_mask;
            body->m_previous_active_collision_range = step_start.active_collision_range;
            body->m_tracking_initialized = true;
            continue;
        }
        body->m_previous_transform = final_transform;
        body->m_previous_type = body->m_type;
        body->m_previous_shape = body->m_shape;
        body->m_previous_enabled = body->enabled;
        body->m_previous_is_trigger = body->is_trigger;
        body->m_previous_mask_tag = body->mask_tag;
        body->m_previous_collision_mask = body->collision_mask;
        body->m_previous_active_collision_range = body->active_collision_range;
        body->m_tracking_initialized = true;
    }
}

bool Physics_Engine::test_collision(Collision_Body& a, Collision_Body& b, Collision* output) const {
    const AABB aa = body_bounds(a);
    const AABB bb = body_bounds(b);
    return test_collision_with_bounds(a, b, aa, bb, output);
}

void Physics_Engine::resolve(Collision& collision) {
    Collision_Body& a = *collision.body_a;
    Collision_Body& b = *collision.body_b;
    const float inverse_a = a.inverse_mass();
    const float inverse_b = b.inverse_mass();
    const float inverse_sum = inverse_a + inverse_b;
    if (inverse_sum <= EPSILON) return;

    const Vec correction = collision.normal * (std::max(collision.penetration - 0.01f, 0.0f) / inverse_sum * 0.8f);
    if (inverse_a > 0.0f) a.transform().pos -= correction * inverse_a;
    if (inverse_b > 0.0f) b.transform().pos += correction * inverse_b;

    Vec relative_velocity = b.velocity - a.velocity;
    const float normal_velocity = vec_dot(relative_velocity, collision.normal);
    if (normal_velocity > 0.0f) return;

    const float restitution = std::min(a.restitution, b.restitution);
    const float impulse_size = -(1.0f + restitution) * normal_velocity / inverse_sum;
    const Vec impulse = collision.normal * impulse_size;
    if (inverse_a > 0.0f) a.velocity -= impulse * inverse_a;
    if (inverse_b > 0.0f) b.velocity += impulse * inverse_b;

    relative_velocity = b.velocity - a.velocity;
    Vec tangent = relative_velocity - collision.normal * vec_dot(relative_velocity, collision.normal);
    tangent = vec_normalized(tangent);
    float friction_impulse = -vec_dot(relative_velocity, tangent) / inverse_sum;
    const float coefficient = std::sqrt(std::max(0.0f, a.friction * b.friction));
    friction_impulse = std::clamp(friction_impulse, -impulse_size * coefficient, impulse_size * coefficient);
    const Vec friction = tangent * friction_impulse;
    if (inverse_a > 0.0f) a.velocity -= friction * inverse_a;
    if (inverse_b > 0.0f) b.velocity += friction * inverse_b;
}

std::vector<Collision_Body*> Physics_Engine::query_overlaps(const Collision_Body& body, Mask_Tag mask) const {
    std::vector<Collision_Body*> results;
    const AABB query_bounds = body_bounds(body);
    Collision_Body& mutable_body = const_cast<Collision_Body&>(body);

    for (Collision_Body* candidate : m_bodies) {
        if (!candidate || candidate == &body || !candidate->enabled ||
            (candidate->mask_tag & mask) == 0) {
            continue;
        }
        const AABB candidate_bounds = body_bounds(*candidate);
        if (!overlaps(query_bounds, candidate_bounds)) continue;
        Collision ignored;
        if (test_collision_with_bounds(
                mutable_body, *candidate, query_bounds, candidate_bounds, &ignored)) {
            results.push_back(candidate);
        }
    }

    return results;
}

Raycast_Hit Physics_Engine::raycast(const Vec& origin, const Vec& direction, float max_distance, Mask_Tag mask, const Collision_Body* ignored_body) const {
    Raycast_Hit result;
    const Vec ray_direction = vec_normalized(direction);
    if (vec_length_squared(ray_direction) <= EPSILON || max_distance < 0.0f) return result;

    float closest_distance = max_distance + 1.0f;
    for (Collision_Body* body : m_bodies) {
        if (!body || body == ignored_body || !body->enabled ||
            (body->mask_tag & mask) == 0) {
            continue;
        }

        const AABB bounds = body_bounds(*body);
        float bounds_entry = 0.0f;
        float bounds_exit = max_distance;
        if (!ray_box_interval(
                origin, ray_direction, bounds.min, bounds.max,
                max_distance, bounds_entry, bounds_exit) ||
            bounds_entry > closest_distance) {
            continue;
        }

        float hit_distance = 0.0f;
        if (!ray_shape_distance(
                *body, origin, ray_direction,
                std::min(max_distance, closest_distance), hit_distance) ||
            hit_distance >= closest_distance) {
            continue;
        }

        closest_distance = hit_distance;
        result.hit = true;
        result.body = body;
        result.distance = hit_distance;
        result.point = origin + ray_direction * hit_distance;
        result.normal = surface_normal(*body, result.point, ray_direction);
    }

    return result;
}

} // namespace Physics
