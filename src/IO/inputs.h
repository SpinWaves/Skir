#ifndef __INPUTS__
#define __INPUTS__

#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdint.h>

typedef struct
{
    SDL_Event events;
    bool keyboard[SDL_NUM_SCANCODES];
    bool mouse[8];
    bool quit;
} Inputs;

void initInput(Inputs *in);
void updateInput(Inputs *in);
bool getKey(Inputs *in, const SDL_Scancode key);
bool getMouse(Inputs *in, const uint8_t button);

#endif // __INPUTS__
