#ifndef ENTITY_H
#define ENTITY_H

#include "raylib.h"
#include "board.h"


typedef struct Game Game;

typedef enum {
    ENTITY_PLAYER,
    ENTITY_ENEMY,
} EntityType;

typedef struct {
    EntityType type;
    Vector2 pos;
    int hp;
    int isAlive;
    Texture2D texture;
} Entity;

void InitEntity(Entity *entity, Vector2 pos, int hp, Texture2D *texture, EntityType type);
void DrawEntity(Entity *entity, Board *board);
void UpdateEntity(Entity *entity, Game* game, Board *Board, Vector2 pos);

#endif