#include "button.h"
#include "raylib.h"



void InitButton(Button *button, int x, int y, Texture2D texture){
    button->hover = 0;
    button->x = x;
    button->y = y;
    button->texture = texture;
    button->textureHover = texture;
}

void DrawButton(Button *button){
    if (button->hover) {
        DrawTexture(button->textureHover, button->x, button->y, WHITE);
    } else {
        DrawTexture(button->texture, button->x, button->y, WHITE);
    }
}

void isHovering(Button *button){
    Vector2 mousePos = GetMousePosition();
    if (mousePos.x >= button->x && mousePos.x <= button->x + button->texture.width && mousePos.y >= button->y && mousePos.y <= button->y + button->texture.height){
        button->hover = 1;
    } else {
        button->hover = 0;
    }
}

int isClicked(Button *button){
    Vector2 mousePos = GetMousePosition();
    if (mousePos.x >= button->x && mousePos.x <= button->x + button->texture.width && mousePos.y >= button->y && mousePos.y <= button->y + button->texture.height){
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
            return 1;
        }
    }
    return 0;
}

