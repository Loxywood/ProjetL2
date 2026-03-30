#include "menu.h"
#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>


//dessiner le rectangle du bouton et ecrire au milieu de le text
void drawButton(Menu *m){
    for ( int i =0; i<m->nButton; i++){
        Button b = m->buttons[i];
        DrawRectangleRec(b.rect, b.color);
        DrawText(b.text, b.posText, b.rect.y, b.rect.height, b.colorT);
    }
}

//regarde pour chaque bouton si la souris est dessus et si elle clic
void actionButton(Menu *m,int *state){
    for (int i = 0; i<m->nButton; i++){
        Button *b = &m->buttons[i];
        if (CheckCollisionPointRec(GetMousePosition(), b->rect)) {
            b->color = DARKPURPLE;
            b->colorT = PURPLE;

            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                b->changeState(state, b->state);
                printf("Bouton cliqué\n");
            }
        }else{
            b->color = DARKBLUE;
            b->colorT = BLUE;

        }
    }
}

//initialise chaque bouton du menu ( rajouter le faite que le text ce fasse a partir d'un fichier ou autre )
void initMenu(Menu* m, int nb){
    int sWidth = GetScreenWidth();
    int sHeight = GetScreenHeight();


    int wScale = sWidth / 2;
    int hScale = sHeight / (nb+1);

    m->nButton = nb;

    m->buttons = malloc(sizeof(Button)*nb);
    for (int i = 0; i<nb; i++){
        int textSize = MeasureText("Bouton", hScale);
        m->buttons[i] = (Button){{wScale/2, (hScale*i)+((i+1)*hScale/(nb+1)), wScale,hScale},"Bouton", DARKBLUE, BLUE, wScale/2+((wScale-textSize)/2),i+1,changeState};
    }
}


void closeMenu(Menu* m){
    free(m->buttons);
}

void changeState(int* state, int newState){
    *state = newState;
}

void runMenu(Menu *menu, int *state){
    BeginDrawing();         
    ClearBackground(RAYWHITE);
    actionButton(menu, state);
    drawButton(menu);
    DrawFPS(10, 10);
    EndDrawing();
}