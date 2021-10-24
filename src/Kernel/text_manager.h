#ifndef __TEXT_MANAGER__
#define __TEXT_MANAGER__

#include <Kernel/text.h>

typedef struct text_link
{
    Text text;
    struct text_link *next;
} text_link;

typedef struct
{
    TTF_Font* default_font;
    text_link* head;
    SDL_Renderer* renderer;
} TextManager;

void initTextManager(TextManager* manager, SDL_Renderer* renderer);
void newText(TextManager* manager, const char* text, int x, int y);
void newText_complete(TextManager* manager, const char* text, int x, int y, int w, int h, SDL_Color* color);
void updateText_TM(TextManager* manager, const char* text_before, const char* text_update);
Text* getText(TextManager* manager, const char* text);
void passText(TextManager* manager, Text* text);
void renderTextManager(TextManager* manager);
void shutdownTextManager(TextManager* manager);

#endif // __TEXT_MANANGER__
