#ifndef BUTTON_H
#define BUTTON_H
#include "raylib.h"

typedef void (*Action)(void* button);

typedef struct Button{
    int x;
    int y;
    Texture2D texture;
}Button;

void InitButton(Button *button, int x, int y, Texture2D texture);
void DrawButton(Button *button);

#endif