#include "menu.h"
#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>



void drawButton(Menu *m){
    for ( int i =0; i<m->nButton; i++){
        Button b = m->buttons[i];
        DrawRectangleRec(b.rect, b.color);
        DrawText(b.text, b.posText, b.rect.y, b.rect.height, b.colorT);
    }
}

void actionButton(Menu *m){
    for (int i = 0; i<m->nButton; i++){
        Button *b = &m->buttons[i];
        if (CheckCollisionPointRec(GetMousePosition(), b->rect)) {
            b->color = DARKPURPLE;
            b->colorT = PURPLE;

            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                printf("Bouton cliqué\n");
            }
        }else{
            b->color = DARKBLUE;
            b->colorT = BLUE;

        }
    }
}

void initMenu(Menu* m, int nb){
    int sWidth = GetScreenWidth();
    int sHeight = GetScreenHeight();


    int wScale = sWidth / 2;
    int hScale = sHeight / (nb+1);

    m->nButton = nb;

    m->buttons = malloc(sizeof(Button)*nb);
    for (int i = 0; i<nb; i++){
        int textSize = MeasureText("Bouton", hScale);
        m->buttons[i] = (Button){{wScale/2, (hScale*i)+((i+1)*hScale/(nb+1)), wScale,hScale},"Bouton", DARKBLUE, BLUE, wScale/2+((wScale-textSize)/2)};
    }
}

void closeMenu(Menu* m){
    free(m->buttons);
}