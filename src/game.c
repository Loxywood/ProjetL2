#include "game.h"
#include "raylib.h"

#define GAME_SCALE 0.3f

void InitGame(Game *game) {
    BoardInit(&game->board, 10, 10, GAME_SCALE);

    Texture2D mob1 = LoadTexture("assets/character.png");
    //Initialisation du héros;
    InitEntity(&game->player, (Vector2){0,0}, 100, &mob1, ENTITY_PLAYER);
    game->state = MENU;
}

void UpdateGame(Game *game){
    //fonction qui gère la logique du jeu
    HandleKey(game, GetKeyPressed());
}

void DrawGame(Game *game){
    //fonction qui gère l'affichage du jeu
    DrawBoard(&game->board);
    DrawEntity(&game->player, &game->board);
}

void HandleKey(Game *game, int key){
    //Pour gérer les inputs du clavier et agir en conséquence.
    //Finalement on transmet un déplacement dans la matrice du plateau plus qu'une position absolue.
    switch (key)
    {
    case KEY_UP:
        UpdateEntity(&game->player,&game->board,(Vector2){-1,0});
        break;
    case KEY_DOWN:
        UpdateEntity(&game->player,&game->board,(Vector2){1,0});
        break;
    case KEY_LEFT:
        UpdateEntity(&game->player,&game->board,(Vector2){0,-1});
        break;
    case KEY_RIGHT:
        UpdateEntity(&game->player,&game->board,(Vector2){0,1});
        break;
    }
}