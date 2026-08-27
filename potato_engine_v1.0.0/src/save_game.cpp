#include "save_game.h"

#include "engine.h"
#include "object.h"
#include "scene.h"
#include "save_game_generated.h"
#include <flatbuffers/flatbuffers.h>
#include <flatbuffers/verifier.h>
#include <algorithm>
#include <fstream>
#include <iterator>
#include <unordered_set>

namespace {
    flatbuffers::Offset<Potato::Save::TransformData> build_transform(
        flatbuffers::FlatBufferBuilder& builder,
        const Transform& transform
    ) {
        Potato::Save::Vec2 pos(transform.pos.x, transform.pos.y);
        Potato::Save::Vec2 size(transform.size.x, transform.size.y);
        Potato::Save::Vec2 rotation(transform.rotation.x, transform.rotation.y);
        return Potato::Save::CreateTransformData(builder, &pos, &size, &rotation);
    }

    Potato::Save::ColorRgba build_color(const Color& color) {
        return Potato::Save::ColorRgba(color.r, color.g, color.b, color.a);
    }

    Vec read_vec(const Potato::Save::Vec2* vec) {
        if (!vec) return {};
        return {vec->x(), vec->y()};
    }

    Color read_color(const Potato::Save::ColorRgba* color) {
        if (!color) return Color::white();
        return {color->r(), color->g(), color->b(), color->a()};
    }
}

namespace Save_Game {
    Object_State capture_object(const Object& object) {
        Object_State state;
        state.name = object.name;
        state.transform = object.transform;
        state.texture_path = object.texture ? object.texture->get_path() : "";
        state.visible = object.visible;
        state.input_transparent = object.input_transparent;
        state.auto_submit = object.auto_submit;
        state.z_index = object.z_index;
        state.tint = object.tint;
        return state;
    }

    Snapshot capture_current() {
        Snapshot snapshot;
        snapshot.version = CURRENT_VERSION;

        if (Engine::scene_manager) {
            snapshot.scene_id = Engine::scene_manager->current_scene();
            snapshot.scene_name = Engine::scene_manager->current_scene_name();
        }

        if (Engine::save_pool && !Engine::save_pool->empty()) {
            return Engine::save_pool->capture_snapshot();
        }

        if (Engine::object_pool) {
            for (const Object* object : Engine::object_pool->get_all()) {
                if (object) {
                    snapshot.objects.push_back(capture_object(*object));
                }
            }
        }

        return snapshot;
    }

    bool save_current(const std::string& path) {
        return save_snapshot(capture_current(), path);
    }

    bool save_snapshot(const Snapshot& snapshot, const std::string& path) {
        flatbuffers::FlatBufferBuilder builder;
        std::vector<flatbuffers::Offset<Potato::Save::ObjectData>> objects;
        objects.reserve(snapshot.objects.size());

        for (const Object_State& object : snapshot.objects) {
            auto transform = build_transform(builder, object.transform);
            auto texture_path = builder.CreateString(object.texture_path);
            auto name = builder.CreateString(object.name);
            auto tint = build_color(object.tint);

            objects.push_back(Potato::Save::CreateObjectData(
                builder,
                transform,
                texture_path,
                object.visible,
                object.input_transparent,
                object.auto_submit,
                object.z_index,
                &tint,
                name
            ));
        }

        auto scene_name = builder.CreateString(snapshot.scene_name);
        auto object_vector = builder.CreateVector(objects);
        auto save = Potato::Save::CreateSaveGame(
            builder,
            snapshot.version,
            snapshot.scene_id,
            scene_name,
            object_vector
        );

        Potato::Save::FinishSaveGameBuffer(builder, save);

        std::ofstream file(path, std::ios::binary);
        if (!file) return false;

        file.write(
            reinterpret_cast<const char*>(builder.GetBufferPointer()),
            static_cast<std::streamsize>(builder.GetSize())
        );
        return file.good();
    }

    bool load_snapshot(const std::string& path, Snapshot& out_snapshot) {
        std::ifstream file(path, std::ios::binary);
        if (!file) return false;

        std::vector<uint8_t> data{
            std::istreambuf_iterator<char>(file),
            std::istreambuf_iterator<char>()
        };
        if (data.empty()) return false;

        flatbuffers::Verifier verifier(data.data(), data.size());
        if (!Potato::Save::VerifySaveGameBuffer(verifier)) {
            return false;
        }

        const Potato::Save::SaveGame* save = Potato::Save::GetSaveGame(data.data());
        Snapshot snapshot;
        snapshot.version = save->version();
        snapshot.scene_id = save->scene_id();
        snapshot.scene_name = save->scene_name() ? save->scene_name()->str() : "";

        if (const auto* objects = save->objects()) {
            snapshot.objects.reserve(objects->size());
            for (const Potato::Save::ObjectData* object : *objects) {
                if (!object) continue;

                Object_State state;
                state.name = object->name() ? object->name()->str() : "";
                if (const auto* transform = object->transform()) {
                    state.transform.pos = read_vec(transform->pos());
                    state.transform.size = read_vec(transform->size());
                    state.transform.rotation = read_vec(transform->rotation());
                }
                state.texture_path = object->texture_path() ? object->texture_path()->str() : "";
                state.visible = object->visible();
                state.input_transparent = object->input_transparent();
                state.auto_submit = object->auto_submit();
                state.z_index = object->z_index();
                state.tint = read_color(object->tint());

                snapshot.objects.push_back(state);
            }
        }

        out_snapshot = std::move(snapshot);
        return true;
    }

    bool apply_snapshot(const Snapshot& snapshot) {
        if (!Engine::object_pool) return false;

        const std::vector<Object*> current_objects =
            Engine::object_pool->get_all();
        const bool can_use_positional_fallback =
            current_objects.size() == snapshot.objects.size();
        std::unordered_set<Object*> applied;
        std::size_t applied_count = 0;

        for (std::size_t index = 0; index < snapshot.objects.size(); ++index) {
            const Object_State& state = snapshot.objects[index];
            Object* target = state.name.empty()
                ? nullptr
                : Engine::object_pool->find_by_name(state.name);

            // Version-one saves have no names. They can still be restored when
            // the deterministic object layout matches the current session.
            if (!target && can_use_positional_fallback) {
                target = current_objects[index];
            }
            if (!target || applied.find(target) != applied.end()) continue;

            target->transform = state.transform;
            target->visible = state.visible;
            target->input_transparent = state.input_transparent;
            target->auto_submit = state.auto_submit;
            target->z_index = state.z_index;
            target->tint = state.tint;
            applied.insert(target);
            ++applied_count;
        }

        if (Engine::scene_manager && snapshot.scene_id >= 0) {
            Engine::scene_manager->set_scene(snapshot.scene_id);
        }
        return applied_count > 0 || snapshot.objects.empty();
    }

    bool load_and_apply(const std::string& path) {
        Snapshot snapshot;
        return load_snapshot(path, snapshot) && apply_snapshot(snapshot);
    }
}

void Save_Pool::add(Object* object) {
    if (!object || contains(object)) return;
    objects.push_back(object);
}

void Save_Pool::remove(Object* object) {
    if (!object) return;

    auto it = std::remove(objects.begin(), objects.end(), object);
    objects.erase(it, objects.end());
}

void Save_Pool::clear() {
    objects.clear();
}

bool Save_Pool::contains(const Object* object) const {
    return std::find(objects.begin(), objects.end(), object) != objects.end();
}

bool Save_Pool::empty() const {
    return objects.empty();
}

std::vector<Object*> Save_Pool::get_all() const {
    return objects;
}

Save_Game::Snapshot Save_Pool::capture_snapshot() const {
    Save_Game::Snapshot snapshot;

    if (Engine::scene_manager) {
        snapshot.scene_id = Engine::scene_manager->current_scene();
        snapshot.scene_name = Engine::scene_manager->current_scene_name();
    }

    snapshot.objects.reserve(objects.size());
    for (const Object* object : objects) {
        if (object) {
            snapshot.objects.push_back(Save_Game::capture_object(*object));
        }
    }

    return snapshot;
}
