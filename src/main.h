// main.h - shared declarations for main.cpp
#ifndef POTATO_MAIN_H
#define POTATO_MAIN_H

#include <SDL3/SDL.h>
#include <SDL3/SDL_gpu.h>
#include <iostream>
#include "engine/potato-engine.h"
#include "engine/potato-script-registry.h"
#include "engine/potato-structures.h"
#include "engine/potato-texture.h"
#include "engine/potato-gameobject.h"
#include "engine/potato-utils.h"

// The program-wide engine instance is defined in main.cpp
extern potato_engine engine;
extern bool running;
extern SDL_Event event;
extern Uint64 last_time;
//extern float delta_time;

#endif // POTATO_MAIN_H
