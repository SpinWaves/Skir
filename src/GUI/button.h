#ifndef __BUTTON__
#define __BUTTON__

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>

#include <Kernel/text.h>

typedef struct
{
    SDL_Rect* coords;
    bool is_activated;
    void (*f)();
    SDL_Color* color;
    Text* text;
    SDL_Renderer* renderer;
} Button;

Button* createButton(SDL_Renderer* renderer, const char* text, int x, int t, int w, int h, int r, int g, int b);
void setFunctionCall(Button* button, void (*f)());
bool isDown(Button* button);
void renderButton(Button* button);
void updateButton(Button* button);
void destroyButton(Button* button);

#endif // __BUTTON__
