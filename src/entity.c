#include "entity.h"
#include "raylib.h"

void InitEntity(Entity *entity, Vector2 pos, int hp, Texture2D *texture, EntityType type) {
    entity->isAlive = 1; // 1 vivant 0 mort
    entity->pos = pos;
    entity->hp = hp;
    entity->type = type;
    entity->texture = *texture;
}

void DrawEntity(Entity *entity, Board *board) {
    
    DrawTexture(entity->texture, (int)entity->pos.x, (int)entity->pos.y, WHITE);
}

void UpdateEntity(Entity *entity, Board *board, Vector2 pos){
    //Update logiquement la position de l'entité
    entity->pos = pos;
}