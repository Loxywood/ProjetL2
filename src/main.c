#include <stdio.h>
#include "game.h"
#include "menu.h"
#include "raylib.h"

int main(void)
{
    //Ouverture de la fenêtre :
    InitWindow(960, 540, "Test Raylib");
    Game game;
    Menu menu;
    int state = 0;

    InitGame(&game);
    initMenu(&menu,5);
    SetTargetFPS(60);

    //Game loop.
    while (!WindowShouldClose())
    {
        switch (state){
        case 1:
            runGame(&game);
            break;
        
        default:
            runMenu(&menu, &state);
        }
    }

    closeMenu(&menu);
    CloseWindow();
    return 0;
}