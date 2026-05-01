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
    HandleKey(game, GetKeyPressed());
}

void DrawGame(Game *game){
    //fonction qui gère l'affichage du jeu
    DrawBoard(&game->board);
    DrawEntity(&game->player, &game->board);
}

/*void keyPressed(Game *game, int key){
    //Pour gérer les inputs du clavier et agir en conséquence.
}*/

void HandleKey(Game *game, int key){
    //Pour gérer les inputs du clavier et agir en conséquence.
    switch (key)
    {
    case KEY_UP:
        game->player.pos.y -= 10;
        break;
    case KEY_DOWN:
        game->player.pos.y += 10;
        break;
    case KEY_LEFT:
        game->player.pos.x -= 10;
        break;
    case KEY_RIGHT:
        game->player.pos.x += 10;
        break;
    }
}