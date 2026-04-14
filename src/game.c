#include "game.h"

void InitGame(Game *game) {
    BoardInit(&game->board, 10, 10);
}

void DrawGame(Game *game){
    //fonction uqi gère l'affiche du jeu
    DrawBoard(&game->board);
}

void UpdateGame(Game *game){
    //fonction qui gere la logique du jeu
}