#ifndef ENTITY_H
#define ENTITY_H

#include "raylib.h"
#include "board.h"

//forward déclaaration pour utiliser l'adresse game
typedef struct Game Game;

typedef enum {
    ENTITY_PLAYER,
    ENTITY_ENEMY,
    ENTITY_POUCH,
    ENTITY_SPARCHU,
} EntityType;

typedef struct {
    EntityType type;
    Vector2 pos;
    int hp;
    int isAlive;
    Texture2D texture;
    int coolDown ;
    bool ready ;
} Entity;

void InitEntity(Entity *entity, Vector2 pos, int hp, Texture2D *texture, EntityType type);
void DrawEntity(Entity *entity, Board *board);
void UpdateEntity(Entity *entity, Board *Board, Vector2 pos);

void GetStun(Game* game, Entity * entity) ;

void GetBetter(Game* game, Entity * entity) ;

void GetReady(Game* game, Entity * entity) ;

void Attack(Game* game, Entity * entity) ;

#endif