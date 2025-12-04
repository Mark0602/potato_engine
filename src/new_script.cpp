#include "engine/potato-script-base.h"
#include "engine/potato-script-registry.h"
#include <iostream>

class new_script : public potato_script {
public:
    void on_start() override {
        // Called when the script starts
        std::cout << "New script started!" << std::endl;
    }

    void on_update(float delta_time) override {
        // Called every frame
    }

    void on_render() override {
        // Called during render phase - useful for debug drawing, UI, etc.
    }

    void on_event(const SDL_Event& event) override {
        // Called when an event occurs
    }

    void on_destroy() override {
        // Called when the script is destroyed
    }
};

// Automatically register this script
REGISTER_SCRIPT(new_script)
