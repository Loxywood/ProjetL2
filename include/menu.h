#ifndef MENU_H
#define MENU_H

#include "raylib.h"

typedef struct {
    Rectangle rect;
    char* text;
    Color color;
    Color colorT;
    int posText;
} Button;

typedef struct{
    int nButton;
    Button* buttons; 
} Menu;

void drawButton(Menu* b);
void actionButton(Menu* b);
void initMenu(Menu* m, int nb);
void closeMenu(Menu* m);

#endif