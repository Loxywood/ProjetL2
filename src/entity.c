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
    entity->coolDown = 0 ;
    entity->ready = 0 ;
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

void GetStun(Game* game, Entity * entity){
    entity->coolDown = 2 ;
    entity->ready = false ;
    switch (entity->type)
    {
    case ENTITY_POUCH:
        entity->texture = game->sprite[1] ;
        break;
    
    case ENTITY_SPARCHU:
        entity->texture = game->sprite[4] ;
        break;
    }

}

void GetBetter(Game* game, Entity * entity){
    entity->coolDown--;
    if (entity->coolDown == 0){
        switch (entity->type)
        {
        case ENTITY_POUCH:
            entity->texture = game->sprite[0] ;
            break;
        
        case ENTITY_SPARCHU:
            entity->texture = game->sprite[3] ;
            break;
        }
    }
}

void GetReady(Game* game, Entity * entity){
    entity->ready = 3 ;
    switch (entity->type)
    {
    case ENTITY_POUCH:
        entity->texture = game->sprite[2] ;
        break;
    
    case ENTITY_SPARCHU:
        entity->texture = game->sprite[5] ;
        break;
    }
}

void Attack(Game* game, Entity * entity){
    entity->ready = 0 ;
    entity->hp++ ;
    Explosion(game, entity->pos, 1, Deals) ;
    switch (entity->type)
        {
        case ENTITY_POUCH:
            entity->texture = game->sprite[0] ;
            break;
        
        case ENTITY_SPARCHU:
            entity->texture = game->sprite[3] ;
            break;
        }
}

void Dash(Game* game, Entity* entity){
    while (entity->ready > 0){
        Move(game, entity->pos, SimplePath(game, entity->pos, game->player.pos), true )  ;
        entity->ready-- ;
    }

    switch (entity->type)
        {
        case ENTITY_POUCH:
            entity->texture = game->sprite[0] ;
            break;
        
        case ENTITY_SPARCHU:
            entity->texture = game->sprite[3] ;
            break;
        }

}