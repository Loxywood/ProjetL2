#include "raylib.h"
#include "game.h"
#include <stdio.h>

int main(void)
{
    //Ouverture de la fenêtre :
    InitWindow(960, 540, "Projet L2 info");
    SetTargetFPS(60);
    
    Game game;
    InitGame(&game);

    //Game loop.
    while (!WindowShouldClose())
    {
        //UpdateGame(&game);
        
        BeginDrawing();         
        ClearBackground(SKYBLUE);

        

        UpdateGame(&game);
        DrawGame(&game);
        EndDrawing();
        
    }
    CloseWindow();
    return 0;
}