#ifndef BOARD_H
#define BOARD_H

#include "tile.h"

typedef struct board
{
    //dimension de la matrice
    int width;
    int height;
    //tableau de tiles
    Tile **tiles;
    //position de départ du plateau
    int startX;
    int startY;
    //echelle de rendue des tiles
    float tile_scale;
}Board;

void BoardInit(Board *board, int width, int height, float scale);
void DrawBoard(Board *board);

#endif