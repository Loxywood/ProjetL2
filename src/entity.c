#include "entity.h"
#include "raylib.h"

void InitEntity(Entity *entity, int posX, int posY, int hp, Texture2D *texture, EntityType type) {
    entity->isAlive = 1; // 1 vivant 0 mort
    entity->texture = *texture;
    entity->type = type;
    
    entity->posX = posX;
    entity->posY = posY;
    entity->hp = hp;
}

void DrawEntity(Entity *entity, Board *board) {
    Vector2 pos = GetCellCenter(board->tiles[entity->posX][entity->posY], board->tile_scale);
    pos.x -= (entity->texture.width * board->tile_scale) / 2.0f;
    pos.y -= (entity->texture.height * board->tile_scale); 
                
    DrawTextureEx(entity->texture, pos, 0.0, board->tile_scale, WHITE);
}
