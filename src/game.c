#include "game.h"
#include "raylib.h"

#define GAME_SCALE 0.3f

void InitGame(Game *game) {
    BoardInit(&game->board, 10, 10, GAME_SCALE);

    Texture2D mob1 = LoadTexture("assets/character.png");
    //Initialisation du héros;
    InitEntity(&game->player, (Vector2){0,0}, 100, &mob1, ENTITY_PLAYER);
}

void UpdateGame(Game *game){
    //fonction qui gère la logique du jeu
    Vector2 mousePosition = GetMousePosition();
    UpdateEntity(&game->player, &game->board,mousePosition);
}

void DrawGame(Game *game){
    //fonction qui gère l'affichage du jeu
    DrawBoard(&game->board);
    DrawEntity(&game->player, &game->board);
}