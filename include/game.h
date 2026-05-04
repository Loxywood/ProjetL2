#ifndef GAME_H
#define GAME_H

#include "board.h"
#include "entity.h"

typedef enum{
        FIGHT,
        MENU,
        SETTINGS,
        DIALOG
}GameState;

typedef struct {
        Board board;
        Entity player;
        Entity enemies[10];
        int enemyAliveCount;
        GameState state;
}Game;

void InitGame(Game *game);
void DrawGame(Game *game);
void StateManager(Game *game);

#endif
