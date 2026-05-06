#ifndef GAME_H
#define GAME_H

#include "tile.h"
#include <string.h>
#include "board.h"
#include "entity.h"

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
}Game;

bool IsEmpty(Game *game, Vector2 V) ;

bool IsWall(Game *game, Vector2 V) ;

int GetArea(int size) ;



void Push(Game *game, Vector2 origin, Vector2 aim) ;

void Attack(Game *game, Vector2 origin, Vector2 aim) ;

void EnemyDeath(Game *game, Vector2 pos) ;



Entity* ENtityAt(Game *game, Vector2 V) ;

void Explosion(Game *game, Vector2 V, int radius) ;



void createDataMouv(int area, dataMove *D) ;

void initAcces(int area,dataMove *D) ;

void initKnown(int area,dataMove *D) ;

void initNext(int area,dataMove *D) ;

void addKnown(dataMove *D, int x, int y, int cap);

void addAcces(dataMove *D, int x, int y, int cap) ;

void addNext(dataMove *D, int x, int y, int cap) ;



int isIn(Vector2 * liste, int size, int x, int y) ; //pas besoin de data supplementaire

void AddZone(Game *game, dataMove *D, int x, int y, int area) ;

void FindZone(Game *game, dataMove *D, int x, int y, int area, int radius) ;








void InitGame(Game *game);
void DrawGame(Game *game);
void UpdateGame(Game *game);
void AddEnnemi(Game *game, Vector2 V) ;
void AddWall(Game *game, Vector2 V) ;
//void KeyPressed(Game *game, int key);
void HandleKey(Game *game, int key);

#endif
