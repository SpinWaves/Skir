#include <Kernel/text.h>
#include <Kernel/log.h>

void initText(Text* t, SDL_Renderer* renderer, const char* text, SDL_Color* color, TTF_Font* font)
{
    t->text = text;
    t->font = font;
    t->color = color;
    if(font == NULL)
        log_report(FATAL_ERROR, "Text: font is NULL");    
    SDL_Surface* surface = TTF_RenderText_Solid(font, text, *color);
    t->texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    int texW = 0;
    int texH = 0;
    SDL_QueryTexture(t->texture, NULL, NULL, &texW, &texH);
    SDL_Rect dstrect = { 0, 0, texW, texH };
    t->rect = &dstrect;
}
void scaleText(Text* t, int x, int y, int w, int h)
{
    SDL_Rect rect = {x, y, w, h};
    t->rect = &rect;
}
void renderText(Text* t, SDL_Renderer* renderer)
{
    SDL_RenderCopy(renderer, t->texture, NULL, t->rect);
}
void deleteText(Text* t)
{
    SDL_DestroyTexture(t->texture);
}
