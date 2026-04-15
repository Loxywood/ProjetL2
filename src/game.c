#include "game.h"
#include "raylib.h"

#define GAME_SCALE 0.3f

void InitGame(Game *game) {
    BoardInit(&game->board, 10, 10, GAME_SCALE);

    Texture2D mob1 = LoadTexture("assets/character2.png");
    //void InitEntity(Entity *entity, int posX, int posY, int hp, Texture2D *texture, EntityType type);
    InitEntity(&game->enemies[0], 1, 1, 20, &mob1, ENTITY_ENEMY);
}

void DrawGame(Game *game){
    //fonction uqi gère l'affiche du jeu
    DrawBoard(&game->board);
    DrawEntity(&game->enemies[0], &game->board);
}

void UpdateGame(Game *game){
    //fonction qui gere la logique du jeu
}