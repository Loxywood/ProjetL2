#include "button.h"
#include "raylib.h"

void initButton(Button* b, int x, int y, int width, int height, const char* text, int textX, int textY, Color rectColorOff, Color rectColorOn, Color textColorOff, Color textColorOn, void* data, int state, Action action){
    *b = (Button){
        .rect = {x, y, width, height},
        .text = text,
        .rectColorOff = rectColorOff,
        .rectColorOn = rectColorOn,
        .textColorOff = textColorOff,
        .textColorOn = textColorOn,
        .textX = textX,
        .textY = textY,
        .data = data,
        .state = state,
        .action = action
    };
}

void drawButtonOff(Button* b){
    DrawRectangleRec(b->rect, b->rectColorOff);
    DrawText(b->text, b->textX, b->textY, b->rect.height, b->textColorOff);
}

void drawButtonOn(Button* b){
    DrawRectangleRec(b->rect, b->rectColorOn);
    DrawText(b->text, b->textX, b->textY, b->rect.height, b->textColorOn);
}