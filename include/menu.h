#ifndef MENU_H
#define MENU_H

#include "raylib.h"

typedef void (*ChangeState)(int* state, int newState);

typedef struct {
    Rectangle rect;
    char* text;
    Color color;
    Color colorT;
    int posText;
    int state;
    ChangeState changeState;

} Button;

typedef struct{
    int nButton;
    Button* buttons; 
} Menu;

void changeState(int* state, int newState);
void drawButton(Menu* b);
void actionButton(Menu* b,int* state);
void initMenu(Menu* m, int nb);
void closeMenu(Menu* m);
void runMenu(Menu* menu, int* state);

#endif