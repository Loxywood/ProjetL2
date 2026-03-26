#include "game.h"

void InitGame(Game *game) {
    BoardInit(&game->board, 10, 10, 0.3);
}