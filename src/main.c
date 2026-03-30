#include <stdio.h>
#include "game.h"
#include "menu.h"

int main(void)
{
    //Ouverture de la fenêtre :
    InitWindow(960, 540, "Test Raylib");
    Game game;
    Menu menu;

    InitGame(&game);
    initMenu(&menu);
    SetTargetFPS(60);

    //Game loop.
    while (!WindowShouldClose())
    {
        BeginDrawing();         
        //ClearBackground(RAYWHITE);
        //DrawBoard(&game.board);
        
        actionButton(&menu);
        drawButon(&menu);
        

        EndDrawing();
    
    }

    closeMenu(menu);
    CloseWindow();
    return 0;
}