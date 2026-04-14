#include <stdio.h>
#include "game.h"

int main(void)
{
    //Ouverture de la fenêtre :
    InitWindow(1920, 1080, "Test Raylib");
    Game game;

    InitGame(&game);
    SetTargetFPS(60);

    //Game loop.
    while (!WindowShouldClose())
    {
        BeginDrawing();         
        ClearBackground(SKYBLUE);
        DrawBoard(&game.board);
        EndDrawing();
    
    }
    CloseWindow();
    return 0;
}