#include <GUI/button.h>
#include <Kernel/Memory/memory.h>

Button* createButton(SDL_Renderer* renderer, const char* text, int x, int y, int w, int h, int r, int g, int b)
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

    SDL_Color white = { 255, 255, 255, 255 };
    button->text = custom_malloc(sizeof(Text));
    button->font = TTF_OpenFont(MAIN_DIR"src/fonts/OpenSans-Regular.ttf", 15);
    initText(button->text, button->renderer, text, &white, button->font);

    int rect_text_x = button->coords->x + (button->coords->w - button->text->rect.w)/2;
    int rect_text_y = button->coords->y + (button->coords->h - button->text->rect.h)/2 + 1;
    scaleText(button->text, rect_text_x, rect_text_y, button->text->rect.w, button->text->rect.h);

    return button;
}
inline void setFunctionCall(Button* button, void (*f)())
{
    button->f = f;
}
inline bool isDown(Button* button)
{
    return button->is_activated;
}
void renderButton(Button* button)
{
    if(!button->trigger)
    {
        SDL_SetRenderDrawColor(button->renderer, 75, 75, 75, 255);
        SDL_RenderFillRect(button->renderer, button->coords);
    }
    else
    {
        SDL_SetRenderDrawColor(button->renderer, 90, 90, 90, 255);
        SDL_RenderFillRect(button->renderer, button->coords);
    }
    if(button->is_activated)
    {
        SDL_SetRenderDrawColor(button->renderer, 35, 35, 35, 255);
        SDL_RenderFillRect(button->renderer, button->coords);
    }
    renderText(button->text, button->renderer);
}
void updateButton(Button* button, Inputs* inputs)
{
    if (   getMouseY(inputs) > button->coords->y
        && getMouseY(inputs) <= button->coords->y + button->coords->h
        && getMouseX(inputs) > button->coords->x
        && getMouseX(inputs) <= button->coords->x + button->coords->w
        && getMouse(inputs, 1, DOWN))
    {
        button->is_button_down = true;
        button->trigger = true;
    }

    if(getMouse(inputs, 1, UP))
        button->is_button_down = false;

    if (   getMouseY(inputs) > button->coords->y
        && getMouseY(inputs) <= button->coords->y + button->coords->h
        && getMouseX(inputs) > button->coords->x
        && getMouseX(inputs) <= button->coords->x + button->coords->w)
        button->trigger = true;
    else
       button->trigger = false;

    if(button->is_button_down && button->is_activated)
    {
        if(button->f != NULL)
            button->f();
        button->is_activated = true;
    }
    else
        button->is_activated = false;
}
void destroyButton(Button* button)
{
    deleteText(button->text);
    custom_free(button->color);
    custom_free(button->coords);
    TTF_CloseFont(button->font);
    custom_free(button);
}
