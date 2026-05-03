#include <stdio.h>
#include "game.h"
#include "menu.h"
#include "raylib.h"

int main(void)
{
    //Ouverture de la fenêtre :
    InitWindow(1920, 1080, "Test Raylib");
    Game game;
    Menu menu;
    int state = 0;

    InitGame(&game);
    InitMenu(&menu);
    SetTargetFPS(60);

    //Game loop.
    while (!WindowShouldClose())
    {
        switch (state){
        case 1:
            runGame(&game);
            break;
        
        default:
            updateMenu(&menu);
            DrawMenu(&menu);
        }
    }
    CloseWindow();
    return 0;
}