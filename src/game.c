#include "game.h"
#include "menu.h"

void InitGame(Game *game) {
    BoardInit(&game->board, 10, 10);
}

void runGame(Game *game){
    BeginDrawing();         
    ClearBackground(RAYWHITE);
    DrawBoard(&game->board);
    EndDrawing();
}