#ifndef SAVE_GAME_H
#define SAVE_GAME_H

#include "color.h"
#include "vec.h"
#include <cstdint>
#include <string>
#include <vector>

struct Object;

namespace Save_Game {
    constexpr uint32_t CURRENT_VERSION = 2;

    struct Object_State {
        std::string name;
        Transform transform;
        std::string texture_path;
        bool visible = true;
        bool input_transparent = false;
        bool auto_submit = true;
        uint8_t z_index = 128;
        Color tint = Color::white();
    };

    struct Snapshot {
        uint32_t version = CURRENT_VERSION;
        int scene_id = 0;
        std::string scene_name;
        std::vector<Object_State> objects;
    };

    Snapshot capture_current();
    bool save_current(const std::string& path);
    bool save_snapshot(const Snapshot& snapshot, const std::string& path);
    bool load_snapshot(const std::string& path, Snapshot& out_snapshot);
    bool apply_snapshot(const Snapshot& snapshot);
    bool load_and_apply(const std::string& path);

    Object_State capture_object(const Object& object);
}

class Save_Pool {
public:
    void add(Object* object);
    void remove(Object* object);
    void clear();

    bool contains(const Object* object) const;
    bool empty() const;
    std::vector<Object*> get_all() const;
    Save_Game::Snapshot capture_snapshot() const;

private:
    std::vector<Object*> objects;
};

#endif
