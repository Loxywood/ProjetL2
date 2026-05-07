#include "entity.h"
#include "game.h"
#include "raylib.h"
#include <stdio.h>

void InitEntity(Entity *entity, Vector2 pos, int hp, Texture2D *texture, EntityType type) {
    entity->isAlive = 1; // 1 vivant 0 mort
    entity->pos = pos;
    entity->hp = hp;
    entity->type = type;
    entity->texture = *texture;
    entity->stun = false ;
}

void DrawEntity(Entity *entity, Board *board) {
    Vector2 pos = GetCellCenter(board->tiles[(int)entity->pos.x][(int)entity->pos.y], board->tile_scale);
    pos.x -= (entity->texture.width * board->tile_scale) / 2.0f;
    pos.y -= (entity->texture.height * board->tile_scale);
    DrawTextureEx(entity->texture, pos, 0.0, board->tile_scale, WHITE);
}

void UpdateEntity(Entity *entity, Board *board, Vector2 pos){
    //Update logiquement la position de l'entité
    Vector2 newPos = (Vector2){entity->pos.x + pos.x, entity->pos.y + pos.y};
    if (newPos.x < 0){
        newPos.x = 0;
    }else if (newPos.x >= board->width){
        newPos.x = board->width - 1;
    }else if (newPos.y < 0){
        newPos.y = 0;
    }else if (newPos.y >= board->height){
        newPos.y = board->height - 1;
    }
    entity->pos = newPos;
        //printf("New position : %f, %f\n", entity->pos.x, entity->pos.y);
}

void GetStun(Entity * entity){
    entity->stun = true ;
}