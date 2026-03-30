#include "menu.h"
#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>



void drawButon(Menu *m){
    for ( int i =0; i<m->nButton; i++){
        DrawRectangleRec(m->buttons[i].rect, m->buttons[i].color);
    }
}

void actionButton(Menu *m){
    for (int i = 0; i<m->nButton; i++){
        Button *b = &m->buttons[i];
        if (CheckCollisionPointRec(GetMousePosition(), b->rect)) {
            b->color = YELLOW;

            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                printf("Bouton cliqué\n");
            }
        }else{
            b->color = DARKBLUE;
        }
    }
}

void initMenu(Menu* m, int nb){
    int sWidth = GetScreenWidth();
    int sHeight = GetScreenHeight();


    int hScale = sHeight / nb;
    int wScale = sWidth / 3;

    m->nButton = nb;

    m->buttons = malloc(sizeof(Button)*nb);

    m->buttons[0] = (Button){{wScale,hScale,wScale,hScale},"Bouton 1", DARKBLUE};
}

void closeMenu(Menu* m){
    free(m->buttons);
}