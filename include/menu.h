#ifndef MENU_H
#define MENU_H

#include "raylib.h"
#include "button.h"

typedef struct{
    int numButton;
    Button* buttons; 
} Menu;

void changeStatePlay(void* data, int newstate);
void drawMenuButton(Menu* b);
void checkMenuButton(Menu* menu);
void initMenu(Menu* m, int numButton, char** texts, int* state);
void closeMenu(Menu* m);
void runMenu(Menu* menu);

#endif;