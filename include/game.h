#include "board.h"

typedef struct {
        Board board;
}Game;

void InitGame(Game *Game);
void runGame(Game *game);