#ifndef MENU_H
#define MENU_H

#include "button.h"
#include "raylib.h"

typedef struct Menu {
    Button startButton;
    Button SettingsButton;
    Button quitButton;
}Menu;

void InitMenu(Menu *menu);
void DrawMenu(Menu *menu);

#endif