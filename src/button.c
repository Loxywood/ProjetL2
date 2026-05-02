#include "button.h"
#include "raylib.h"



void InitButton(Button *button, int x, int y, Texture2D texture){
    button->x = x;
    button->y = y;
    button->texture = texture;
}

void DrawButton(Button *button){
    DrawTexture(button->texture, button->x, button->y, WHITE);
}