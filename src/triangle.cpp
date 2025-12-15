#include "engine/potato-script-base.h"
#include "engine/potato-script-registry.h"
#include <iostream>
#include "main.h"
#include "engine/potato-engine.h"

#include "engine/potato-render.h"
#include "engine/potato-utils.h"

class triangle : public potato_script {
    potato_vertex_buffer* vb = nullptr;

public:
    void on_start() override {
        debug::script_log("Triangle script started", this);

        // Vertex buffer létrehozása 3 vertexhez
        vb = new potato_vertex_buffer(engine.get_device(), 3);
        vb->lock();
        vb->set_vertex_count(3);
        vertex* verts = vb->get_vertices();

        // Háromszög pontjai (ablak közepéhez igazítva, színes csúcsok)
        verts[0].set_position(0.0f, 0.5f);   // felső
        verts[0].set_color(255, 0, 0, 255);  // piros
        verts[1].set_position(-0.5f, -0.5f); // bal alsó
        verts[1].set_color(0, 255, 0, 255);  // zöld
        verts[2].set_position(0.5f, -0.5f);  // jobb alsó
        verts[2].set_color(0, 0, 255, 255);  // kék
        vb->unlock();
    }

    void on_update(float delta_time) override {

        
    }

    void on_render() override {
        if (vb) {
            // Háromszög kirajzolása
            engine.draw_vertex_buffer(vb, vb->get_vertex_count());
        }
    }

    void on_event(const SDL_Event& event) override {
        // Itt nem szükséges semmi
    }

    void on_destroy() override {
        if (vb) {
            delete vb;
            vb = nullptr;
        }
    }
};

// Automatically register this script
REGISTER_SCRIPT(triangle)