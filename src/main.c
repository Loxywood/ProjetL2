#include <stdio.h>
#include "game.h"

int main(void)
{
    //Ouverture de la fenêtre :
    InitWindow(1920, 1080, "Test Raylib");
    SetTargetFPS(60);
    
    Game game;
    InitGame(&game);

    //Game loop.
    while (!WindowShouldClose())
    {
        //UpdateGame(&game);
        
        BeginDrawing();         
        ClearBackground(SKYBLUE);
        DrawGame(&game);
        EndDrawing();
        
    }
    CloseWindow();
    return 0;
}