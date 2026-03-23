#include <stdio.h>
#include "game.h"

int main(void)
{
    //Ouverture de la fenêtre :
    InitWindow(960, 540, "Test Raylib");
    Game game;

    InitGame(&game);
    SetTargetFPS(60);

    //Game loop.
    while (!WindowShouldClose())
    {
        BeginDrawing();         
        ClearBackground(RAYWHITE);
        DrawBoard(&game.board);
        //DrawTile(&tile);
        EndDrawing();
    
    }
    CloseWindow();
    return 0;
}