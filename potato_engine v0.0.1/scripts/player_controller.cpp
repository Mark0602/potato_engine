#include "engine.h"
#include "src/script-registry.h"

class player_controller_script final : public script {
    SCRIPT_ORDER(0)
    SCRIPT_SCENE(-1)

public:

    // Runs on game start, incase of an attached_script, it runs when the object initates.
    void on_start() override {

    }

    // Runs every frame - guess what...
    void on_update(float delta_time) override { 

    }

    // Runs every fram on the global render call, but you likely won't use it much, as auto_submit handles it already
    void on_render() override {}
    // Runs when an SDL_Event occurs, but you likely won't use it much, as every important event can be accessed throught the update with states like Input::
    void on_event(const SDL_Event& event) override {}

    // Runs when the script is destroyed, for example the game closed, or the object got deleted.
    void on_destroy() override {

    }
};

REGISTER_SCRIPT(player_controller_script)
