#ifndef GAME_H
#define GAME_H

#include "board.h"
#include "entity.h"

typedef enum {
        MENU,
        GAME
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
void UpdateGame(Game *game);
//void KeyPressed(Game *game, int key);
void HandleKey(Game *game, int key);

#endif
