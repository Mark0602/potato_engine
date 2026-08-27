#include <SDL3/SDL_main.h>

#include <iostream>
#include <string>
#include <utility>

#include "engine.h"

namespace {

bool parse_frame_rate(const std::string& value, uint32_t& destination) {
    try {
        const int parsed = std::stoi(value);
        if (parsed < 0 || parsed > 1000) return false;
        destination = parsed;
        return true;
    } catch (...) {
        return false;
    }
}

void print_help() {
    std::cout
        << "Potato Engine sandbox\n"
        << "  --gpu                 use the SDL_GPU renderer\n"
        << "  --cpu                 use the SDL renderer\n"
        << "  --fps=N               focused frame limit (0 disables)\n"
        << "  --background-fps=N    unfocused frame limit\n"
        << "  --console             open the debug console\n";
}

} // namespace

int main(int argc, char* argv[]) {
    config::game_config config;
    config::settings settings;

    for (int index = 1; index < argc; ++index) {
        const std::string argument = argv[index] ? argv[index] : "";
        if (argument == "--gpu" || argument == "--renderer=gpu") {
            config.renderer_backend = RendererBackend::GPU;
        } else if (argument == "--cpu" ||
                   argument == "--renderer=cpu") {
            config.renderer_backend = RendererBackend::CPU;
        } else if (argument.rfind("--fps=", 0) == 0) {
            parse_frame_rate(argument.substr(6), settings.target_fps);
        } else if (argument.rfind("--background-fps=", 0) == 0) {
            parse_frame_rate(
                argument.substr(17), settings.background_fps
            );
        } else if (argument == "--console") {
            config.show_console = true;
        } else if (argument == "--help" || argument == "-h") {
            print_help();
            return 0;
        }
    }

    Engine::Application application(std::move(config));
    return application.run();
}
