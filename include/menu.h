#ifndef MENU_H
#define MENU_H

#include "raylib.h"

typedef struct {
    Rectangle rect;
    char* text;
    Color color;
} Button;

typedef struct{
    int nButton;
    Button* buttons; 
} Menu;

void drawButon(Menu* b);
void actionButton(Menu* b);
void initMenu(Menu* m, int nb);
void closeMenu(Menu* m);

#endif