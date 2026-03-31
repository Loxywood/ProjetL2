#ifndef BUTTON_H
#define BUTTON_H
#include "raylib.h"

typedef void (*Action)(void* data, int newState);

typedef struct {
    Rectangle rect;
    char* text;
    Color rectColorOff;
    Color rectColorOn;
    Color textColorOff;
    Color textColorOn;
    int textX;
    int textY;
    char hover;
    
    void* data; 
    int state;
    Action action;
} Button;

void initButton(Button* b ,int x, int y, int width, int height, char* text, int textX, int textY, Color rectColorOff, Color rectColorOn, Color textColorOff, Color textColorOn, void* data, int state, Action action);
void drawButtonOff(Button* b);
void drawButtonOn(Button* b);

#endif