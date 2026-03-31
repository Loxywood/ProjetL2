#include "menu.h"
#include "raylib.h"
#include "button.h"
#include <stdio.h>
#include <stdlib.h>


//initialise chaque bouton du menu ( rajouter le faite que le text ce fasse a partir d'un fichier ou autre )
void initMenu(Menu* menu, int numButton, const char* texts[], int* data){
    //taille de la fenetre
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    //position au centre et espace par bouton a libérer
    int buttonWidth = screenWidth / 2;//largeur du bouton égale a la moitié de la fenetre
    int buttonHeight = screenHeight / (numButton+1);//+1 pour ecrire le bouton a partir du milieu

    menu->numButton = numButton;
    menu->buttons = malloc(sizeof(Button)*numButton);
    if (menu->buttons == NULL){
        printf("erreur malloc impossible");
        return;
    }

    for (int i = 0; i<numButton; i++){
        const char* text = texts[i];
        int textSize = MeasureText(text, buttonHeight);
        initButton(&menu->buttons[i], buttonWidth/2, (buttonHeight*i)+((i+1)*buttonHeight/(numButton+1)), buttonWidth, buttonHeight, text, buttonWidth/2+((buttonWidth-textSize)/2), (buttonHeight*i)+((i+1)*buttonHeight/(numButton+1)), DARKBLUE, DARKPURPLE, BLUE, PURPLE, data, i+1, &changeStatePlay);
    }
}

//dessiner le rectangle du bouton et ecrire au milieu de le text
void drawMenuButton(Menu *menu){
    for ( int i =0; i<menu->numButton; i++ ){
        Button* button = &menu->buttons[i];
        if ( button->hover ){
            drawButtonOn(button);
        }else{
            drawButtonOff(button);
        }
    }
}

//regarde pour chaque bouton si la souris est dessus et si elle clic
void checkMenuButton(Menu *menu){
    for (int i = 0; i<menu->numButton; i++){
        Button *button = &menu->buttons[i];

        if ( CheckCollisionPointRec( GetMousePosition(), button->rect ) ) {
            button->hover = 1;

            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                button->action( button);
                printf("Bouton cliqué\n");
            }
        }else{
            button->hover = 0;
        }
    }
}



void closeMenu(Menu* m){
    free(m->buttons);
}

void changeStatePlay(void* buttonPtr){
    Button* button = (Button*)buttonPtr;
    int* actualState = (int *)button->data;
    *actualState = button->state;
}

void runMenu(Menu *menu){
    BeginDrawing();         
    ClearBackground(RAYWHITE);
    checkMenuButton(menu);
    drawMenuButton(menu);
    DrawFPS(10, 10);
    EndDrawing();
}