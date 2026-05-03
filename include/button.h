#ifndef BUTTON_H
#define BUTTON_H

#include "raylib.h"

typedef struct Button{
    int x;
    int y;
    Texture2D texture;
    Texture2D textureHover;
    int hover;
}Button;

void InitButton(Button *button, int x, int y, Texture2D texture);
void DrawButton(Button *button);
void isHovering(Button *button);

#endif