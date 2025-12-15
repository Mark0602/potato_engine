#include "engine/potato-script-base.h"
#include "engine/potato-script-registry.h"
#include <iostream>
#include "main.h"
#include "engine/potato-engine.h"

class new_script : public potato_script {


public:
    void on_start() override {
        // Inicializációs kód ide jöhet
        debug::script_log("New script started", this);
    }

    void on_update(float delta_time) override {
        // frame frissítési kód ide jöhet
    }

    void on_render() override {
        // egyedi renderelési kód ide jöhet
    }

    void on_event(const SDL_Event& event) override {
        // input kezelés ide jöhet
    }

    void on_destroy() override {
        // tisztítási kód ide jöhet
    }
};

// Automatically register this script
REGISTER_SCRIPT(new_script)