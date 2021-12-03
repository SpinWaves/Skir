#include <GUI/main_menu.h>

static Main_Menu* __menu = NULL;

void initMainMenu()
{
    __menu = custom_malloc(sizeof(Main_Menu));
}
void callMainMenu()
{

}
void updateMainMenu()
{

}
void renderMainMenu()
{

}
void shutdownMainMenu()
{
    custom_free(__menu)
}
