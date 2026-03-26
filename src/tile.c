#include "tile.h"


void InitTile(Tile *tile, Texture2D texture, float posX, float posY) {
    tile->texture = texture;
    tile->posX = posX;
    tile->posY = posY;
}

void DrawTile(Tile *t, float scale) {
    //(Texture2D texture, Vector2 position, float rotation, float scale, Color tint);
    DrawTextureEx(t->texture, (Vector2){t->posX, t->posY}, 0.0, scale, WHITE);
}