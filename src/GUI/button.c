#include <GUI/button.h>
#include <Kernel/Memory/memory.h>

Button* createButton(SDL_Renderer* renderer, const char* text, int x, int t, int w, int h, int r, int g, int b)
{
    Button* button = custom_malloc(sizeof(Button));
    button->coords = custom_malloc(sizeof(SDL_Rect));
    button->coords->x = x;
    button->coords->y = y;
    button->coords->w = w;
    button->coords->h = h;

    button->color = custom_malloc(sizeof(SDL_Color));
    button->color->r = r;
    button->color->g = g;
    button->color->b = b;
    button->color->a = 255;

    button->renderer = renderer;
    button->f = NULL;

    return button;
}
void setFunctionCall(Button* button, void (*f)())
{
    button->f = f;
}
bool isDown(Button* button)
{

}
void renderButton(Button* button)
{

}
void updateButton(Button* button)
{

}
void destroyButton(Button* button)
{

}
