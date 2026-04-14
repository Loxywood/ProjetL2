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

Vector2 GetCellCenter(Tile tile, float scale){
    Vector2 ret = {0, 0};
    ret.x = tile.posX + (tile.texture.width * scale) / 2.0f;
    ret.y = tile.posY + (tile.texture.height * scale) / 4.0f;
    return ret;
}