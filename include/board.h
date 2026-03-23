#include "tile.h"
#include <stdlib.h>

typedef struct board
{
    int width;
    int height;
    Tile **tiles;
    int posX;
    int posY;
}Board;

void BoardInit(Board *board, int width, int height);
void DrawBoard(Board *board);