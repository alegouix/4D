#include <SDL2/SDL.h>

#include "utils.h"

Uint64 _last_tick=0;

void tick(Uint64 fps) {
    Uint64 delay = 1000 / fps;
    Uint64 timeout = _last_tick + delay;
    while (SDL_GetTicks64() < timeout){}

    _last_tick = SDL_GetTicks64();
}