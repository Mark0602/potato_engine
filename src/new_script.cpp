#include "engine/potato-script-base.h"
#include "engine/potato-script-registry.h"
#include "potato-structures.h"
#include <iostream>

#include "engine/potato-gameobject.h"
#include "engine/potato-engine.h"
#include "engine/potato-texture.h"

class new_script : public potato_script {

gameobject* player;
potato_texture *player_texture;

public:
    void on_start() override {
        

        player = new gameobject("Player");
        player->set_position(100.0f, 150.0f);

        
        player_texture = new potato_texture("assets/imgs/player.png");
        player_texture->load();
        player->set_texture(player_texture);

        // Called when the script starts
        std::cout << "New script started!" << std::endl;
    }

    void on_update(float delta_time) override {
        // Called every frame
    }

    void on_render() override {
        // Called during render phase - useful for debug drawing, UI, etc.

        player->render_texture();
    }

    void on_event(const SDL_Event& event) override {
        // Called when an event occurs
    }

    void on_destroy() override {
        // Called when the script is destroyed
        player_texture->unload();
        delete player_texture;
        delete player;

    }
};

// Automatically register this script
REGISTER_SCRIPT(new_script)
