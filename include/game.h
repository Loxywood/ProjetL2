#ifndef GAME_H
#define GAME_H

#include "tile.h"
#include <string.h>
#include "board.h"
#include "entity.h"
#include <time.h>


typedef struct {
    Vector2 *acces ;
    int cursor_a  ;
    Vector2 *known ;
    int cursor ;
    Vector2 *next ;
    int cursor_n ;
} dataMove ;

typedef enum {
        MENU,
        GAME
}GameState;

typedef struct Game{
        Board board;
        Entity player;
        Entity enemies[10];
        Entity walls[20] ;
        int enemyAliveCount;
        int wallCount ;
        GameState state;
        Texture2D sprite[10] ;
        Texture2D HPtexture ;
        int turn ;
        int start ;
        int end  ;
        int speed ;
}Game;

bool IsEmpty(Game *game, Vector2 V, bool playerIncluded) ;

bool IsWall(Game *game, Vector2 V) ;

int GetArea(int size) ;

bool IsInBound(Board *board, Vector2 pos) ;



bool Push(Game *game, Vector2 origin, Vector2 aim) ;

bool Move(Game * game, Vector2 origin, Vector2 dir, bool push) ;

bool Deals(Game *game, Vector2 origin, Vector2 aim) ;

void EnemyDeath(Game *game, Vector2 pos) ;



Entity* ENtityAt(Game *game, Vector2 V) ;

void Explosion(Game *game, Vector2 V, int radius, bool (*effect)(Game*, Vector2, Vector2)) ;



void createDataMouv(int area, dataMove *D) ;

void initAcces(int area,dataMove *D) ;

void initKnown(int area,dataMove *D) ;

void initNext(int area,dataMove *D) ;

void addKnown(dataMove *D, int x, int y, int cap);

void addAcces(dataMove *D, int x, int y, int cap) ;

void addNext(dataMove *D, int x, int y, int cap) ;



int IsIn(Vector2 * liste, int size, int x, int y) ; //pas besoin de data supplementaire

void AddZone(Game *game, dataMove *D, int x, int y, int area, bool trough) ;

void FindZone(Game *game, dataMove *D, int x, int y, int area, int radius, bool trough) ;

Vector2* GetPath(Game* game, Vector2 pos, Vector2 aim, int length) ;

Vector2 RandomDir(Game * game, Vector2 pos) ;

Vector2 SimplePath(Game *game, Vector2 pos, Vector2 aim) ;

void EnemiesTurn(Game* game) ;

void PlayerTurn(Game * game, Entity *player, Vector2 direction) ;

void ListDir(Vector2 * dir) ;

void InitGame(Game *game);
void DrawGame(Game *game);
void UpdateGame(Game *game);

void AddEnnemiPouch(Game *game, Vector2 V) ;
void AddEnnemiSparchu(Game *game, Vector2 V) ;
void AddEnnemiBoss(Game *game, Vector2 V) ;


void AddWall(Game *game, Vector2 V) ;

//void KeyPressed(Game *game, int key);
void HandleKey(Game *game, int key);

#endif
