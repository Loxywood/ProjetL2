#include "board.h"

typedef struct {
        Board board;
}Game;

void InitGame(Game *game);
void DrawGame(Game *game);
void UpdateGame(Game *game);