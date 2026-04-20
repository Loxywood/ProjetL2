#include "button.h"
#include "raylib.h"

void initButton(Button* b, int x, int y, int width, int height, const char* text, Color rectColorOff, Color rectColorOn, Color textColorOff, Color textColorOn, void* data, int state, Action action){
    int textSize = MeasureText(text, height);
    
    *b = (Button){
        .rect = {x-width/2, y-height/2, width, height},
        .text = text,
        .rectColorOff = rectColorOff,
        .rectColorOn = rectColorOn,
        .textX = x-(textSize/2),
        .textY = y-height/2,
        .textColorOff = textColorOff,
        .textColorOn = textColorOn,
        .data = data,
        .state = state,
        .action = action,
        .hover = 0
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