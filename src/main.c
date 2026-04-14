#include <stdio.h>
#include "game.h"

int main(void)
{
    //Ouverture de la fenêtre :
    InitWindow(960, 540, "Test Raylib");
    SetTargetFPS(60);
    
    Game game;
    InitGame(&game);

    while (!WindowShouldClose()){
        
        //UpdateGame(&game);

        BeginDrawing();         
        ClearBackground(RAYWHITE);
        DrawGame(&game);
        EndDrawing();
    
    }
    CloseWindow();
    return 0;
}