#include "game.h"
#include "raylib.h"

#define GAME_SCALE 0.3f

void InitGame(Game *game) {
    BoardInit(&game->board, 10, 10, GAME_SCALE);

    Texture2D mob1 = LoadTexture("assets/character.png");
    //void InitEntity(Entity *entity, int posX, int posY, int hp, Texture2D *texture, EntityType type);
    InitEntity(&game->enemies[0], 1, 1, 20, &mob1, ENTITY_ENEMY);
}

void DrawGame(Game *game){
    //fonction qui gère l'affichage du jeu
    DrawBoard(&game->board);
    DrawEntity(&game->enemies[0], &game->board);
}

void StateManager(Game *game){
    switch (game->state)
    {
    case FIGHT:
        //Il faudrait que si ESC est préssé, le menu s'affiche.utilisation der isPressed(ESC).
        break;
    case MENU:
        //Si ESC est préssé ou "Jouer", le menu disparaisse.
        break;
    case SETTINGS:
        //Seulement dans le cas où le bouton "Settings" du menu est préssé.
        break;
    case DIALOG:
        //Déclencher en cas d'évènement à définir...
        break;
    default:
        break;
    }
}