#ifndef GAME_H
#define GAME_H

#include "board.h"
#include "entity.h"

typedef struct {
        Board board;
        Entity player;
        Entity enemies[10];
        int enemyAliveCount;
}Game;

void InitGame(Game *game);
void DrawGame(Game *game);
void UpdateGame(Game *game);

#endif
