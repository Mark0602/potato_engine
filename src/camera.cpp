#include "camera.h"

#include "object.h"

#include <algorithm>
#include <cmath>

void Camera::set_viewport(float width, float height) {
    m_viewport_width = std::max(1.0f, width);
    m_viewport_height = std::max(1.0f, height);
    apply_bounds();
}

void Camera::set_position(Vec position) {
    m_position = position;
    apply_bounds();
}

void Camera::move(Vec delta) {
    m_position.x += delta.x;
    m_position.y += delta.y;
    apply_bounds();
}

Vec Camera::get_position() const {
    return m_position;
}

void Camera::set_zoom(float zoom) {
    m_zoom = std::max(0.01f, zoom);
    apply_bounds();
}

float Camera::get_zoom() const {
    return m_zoom;
}

void Camera::set_rotation(float rotation) {
    m_rotation = rotation;
}

float Camera::get_rotation() const {
    return m_rotation;
}

void Camera::shake(float intensity, float duration) {
    (void)intensity;
    (void)duration;
    // Reserved for a future trauma/noise based camera shake implementation.
}

Vec Camera::world_to_screen(Vec world_pos) const {
    return {
        (world_pos.x - m_position.x) * m_zoom,
        (world_pos.y - m_position.y) * m_zoom
    };
}

Vec Camera::screen_to_world(Vec screen_pos) const {
    return {
        (screen_pos.x / m_zoom) + m_position.x,
        (screen_pos.y / m_zoom) + m_position.y
    };
}

Vec Camera::world_size_to_screen(Vec world_size) const {
    return {
        world_size.x * m_zoom,
        world_size.y * m_zoom
    };
}

Vec Camera::screen_size_to_world(Vec screen_size) const {
    return {
        screen_size.x / m_zoom,
        screen_size.y / m_zoom
    };
}

Transform Camera::world_to_screen(const Transform& world_transform) const {
    return {
        world_to_screen(world_transform.pos),
        world_size_to_screen(world_transform.size),
        world_transform.rotation
    };
}

Transform Camera::screen_to_world(const Transform& screen_transform) const {
    return {
        screen_to_world(screen_transform.pos),
        screen_size_to_world(screen_transform.size),
        screen_transform.rotation
    };
}

bool Camera::can_see(const Transform& world_transform) const {
    Vec view_size = screen_size_to_world({m_viewport_width, m_viewport_height});
    Vec view_min = m_position;
    Vec view_max = m_position + view_size;

    Vec object_min = world_transform.pos;
    Vec object_size = world_transform.size;

    if (object_size.x <= 0.0f || object_size.y <= 0.0f) {
        return object_min.x >= view_min.x && object_min.x <= view_max.x &&
               object_min.y >= view_min.y && object_min.y <= view_max.y;
    }

    Vec object_max = object_min + object_size;

    return object_max.x >= view_min.x &&
           object_min.x <= view_max.x &&
           object_max.y >= view_min.y &&
           object_min.y <= view_max.y;
}

void Camera::follow(Object* target, float smoothing, float dt) {
    if (!target) {
        return;
    }

    const Transform target_transform = target->get_world_transform();
    Vec target_pos = target_transform.pos;
    Vec target_size = target_transform.size;
    Vec centered_target = {
        target_pos.x + (target_size.x * 0.5f) - (m_viewport_width / (2.0f * m_zoom)),
        target_pos.y + (target_size.y * 0.5f) - (m_viewport_height / (2.0f * m_zoom))
    };

    if (smoothing <= 0.0f || dt <= 0.0f) {
        set_position(centered_target);
        return;
    }

    float amount = std::clamp(smoothing * dt, 0.0f, 1.0f);
    set_position({
        m_position.x + (centered_target.x - m_position.x) * amount,
        m_position.y + (centered_target.y - m_position.y) * amount
    });
}

void Camera::set_bounds(Vec min, Vec max) {
    m_bounds_min = min;
    m_bounds_max = max;
    m_use_bounds = true;
    apply_bounds();
}

void Camera::clear_bounds() {
    m_use_bounds = false;
}

void Camera::apply_bounds() {
    if (!m_use_bounds) {
        return;
    }

    Vec view_size = screen_size_to_world({m_viewport_width, m_viewport_height});
    float max_x = std::max(m_bounds_min.x, m_bounds_max.x - view_size.x);
    float max_y = std::max(m_bounds_min.y, m_bounds_max.y - view_size.y);

    m_position.x = std::clamp(m_position.x, m_bounds_min.x, max_x);
    m_position.y = std::clamp(m_position.y, m_bounds_min.y, max_y);
}

Camera_Pool::Camera_Pool() {
    m_active_camera = create(MAIN_CAMERA_NAME);
}

Camera* Camera_Pool::create(const std::string& name) {
    if (name.empty()) {
        return nullptr;
    }

    if (Camera* existing = get(name)) {
        return existing;
    }

    auto camera = std::make_unique<Camera>();
    Camera* raw_camera = camera.get();
    m_cameras.emplace(name, std::move(camera));

    if (!m_active_camera) {
        m_active_camera = raw_camera;
    }

    return raw_camera;
}

Camera* Camera_Pool::get(const std::string& name) {
    auto it = m_cameras.find(name);
    if (it == m_cameras.end()) {
        return nullptr;
    }

    return it->second.get();
}

const Camera* Camera_Pool::get(const std::string& name) const {
    auto it = m_cameras.find(name);
    if (it == m_cameras.end()) {
        return nullptr;
    }

    return it->second.get();
}

bool Camera_Pool::set_active(const std::string& name) {
    Camera* camera = get(name);
    if (!camera) {
        return false;
    }

    m_active_camera = camera;
    return true;
}

bool Camera_Pool::remove(const std::string& name) {
    if (name == MAIN_CAMERA_NAME) {
        return false;
    }

    Camera* camera = get(name);
    if (!camera) {
        return false;
    }

    if (m_active_camera == camera) {
        m_active_camera = main_camera();
    }

    return m_cameras.erase(name) > 0;
}

void Camera_Pool::clear() {
    Camera* main = main_camera();

    for (auto it = m_cameras.begin(); it != m_cameras.end();) {
        if (it->first == MAIN_CAMERA_NAME) {
            ++it;
        } else {
            it = m_cameras.erase(it);
        }
    }

    m_active_camera = main ? main : create(MAIN_CAMERA_NAME);
}
