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
    button->is_button_down = false;

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
void updateButton(Button* button, Inputs* inputs)
{
    if (   getMouseY(inputs) > button->coords.y
        && getMouseY(inputs) <= button->coords.y + button->coords.h
        && getMouseX(inputs) > button->coords.x
        && getMouseX(inputs) <= button->coords.x + button->coords.w
        && button->is_button_down)
        button->trigger = true;

    if(mouse_button_up)
        _button_down = false;

    if (   getMouseY(inputs) > button->coords.y
        && getMouseY(inputs) <= button->coords.y + button->coords.h
        && getMouseX(inputs) > button->coords.x
        && getMouseX(inputs) <= button->coords.x + button->coords.w)
        button->trigger = true;
    else
       button->trigger = false;

    if(mouse_button_up && button->is_activated)
        button->is_activated = true;
    else
        button->is_activated = false;
}
void destroyButton(Button* button)
{

}
