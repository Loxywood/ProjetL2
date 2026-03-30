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

    InitGame(&game);
    initMenu(&menu,5);
    SetTargetFPS(60);

    //Game loop.
    while (!WindowShouldClose())
    {
        BeginDrawing();         
        ClearBackground(RAYWHITE);
        //DrawBoard(&game.board);
        
        actionButton(&menu);
        drawButton(&menu);
        DrawFPS(10, 10);

        EndDrawing();
    
    }

    closeMenu(&menu);
    CloseWindow();
    return 0;
}