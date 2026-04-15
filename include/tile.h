#ifndef TILE_H
#define TILE_H

#include "raylib.h"


typedef struct {
    Texture2D texture;
    float posX;
    float posY;
} Tile;

void InitTile(Tile *tile, Texture2D texture, float posX, float posY);
void DrawTile(Tile *t, float scale);
Vector2 GetCellCenter(Tile tile, float scale);

#endif