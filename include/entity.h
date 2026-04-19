#ifndef ENTITY_H
#define ENTITY_H

#include "raylib.h"
#include "board.h"

typedef enum {
    ENTITY_PLAYER,
    ENTITY_ENEMY,
} EntityType;

typedef struct {
    EntityType type;
    int posX; 
    int posY;
    int hp;
    int isAlive;
    Texture2D texture;
} Entity;

void InitEntity(Entity *entity, int posX, int posY, int hp, Texture2D *texture, EntityType type);
void DrawEntity(Entity *entity, Board *board);

#endif