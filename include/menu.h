#ifndef MENU_H
#define MENU_H
#define BUTTON_COUNT 3

#include "button.h"
#include "raylib.h"
#include "game.h"

typedef struct Menu {
    Button buttons[BUTTON_COUNT];
}Menu;

void InitMenu(Menu *menu);
void DrawMenu(Menu *menu);
void updateMenu(Menu *menu, Game *game);

#endif