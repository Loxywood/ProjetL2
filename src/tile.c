#include "tile.h"

void InitTile(Tile *tile, Texture2D texture, float posX, float posY) {
    tile->texture = texture;
    tile->posX = posX;
    tile->posY = posY;
}

void DrawTile(Tile *t) {
    DrawTexture(t->texture, t->posX, t->posY, RAYWHITE);
}