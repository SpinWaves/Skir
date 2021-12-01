#include <IO/inputs.h>
#include <Kernel/Memory/memory.h>

void initInput(Inputs *in)
{
    for(int i = 0; i < SDL_NUM_SCANCODES; i++)
    {
        in->keyboard[i] = false;
        if(i < 8)
            in->mouse[i] = false;
    }

    in->quit = false;
    in->mx = 0;
    in->my = 0;
}

void updateInput(Inputs *in)
{
    for(int i = 0; i < SDL_NUM_SCANCODES; i++)
    {
        in->keyboard[i] = false;
        if(i < 8)
            in->mouse[i] = false;
    }

    while(SDL_PollEvent(&in->events))
    {
        if(in->events.window.event == SDL_WINDOWEVENT_CLOSE)
            in->quit = true;
        switch(in->events.type)
        {
            case SDL_KEYDOWN: in->keyboard[in->events.key.keysym.scancode] = true; break;
            case SDL_MOUSEBUTTONDOWN: in->mouse[in->events.button.button] = true; break;
            
            default: break;
        }
        if(in->events.type == SDL_MOUSEMOTION) // Mouvement de la souris
        {
                in->mx = in->events.motion.x;
                in->my = in->events.motion.y;
        }
    }
}

bool getKey(Inputs *in, const SDL_Scancode key)
{
    return in->keyboard[key];
}
bool getMouse(Inputs *in, const uint8_t button)
{
    return in->mouse[button];
}

inline int getMouseX(Inputs* in)
{
    return in->mx;
}
inline int getMouseX(Inputs* in)
{
    return in->my;
}
