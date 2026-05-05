
#include "entity.h"
#include "game.h"
#include "raylib.h"
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

#define GAME_SCALE 0.3f

void InitGame(Game *game) {
    BoardInit(&game->board, 10, 10, GAME_SCALE);

    game->enemyAliveCount = 0 ;

    Texture2D mob1 = LoadTexture("assets/character.png");
    //Initialisation du héros;
    InitEntity(&game->player, (Vector2){0,0}, 100, &mob1, ENTITY_PLAYER);
    game->state = MENU;
}

void UpdateGame(Game *game){
    //fonction qui gère la logique du jeu
    HandleKey(game, GetKeyPressed());
}

void DrawGame(Game *game){
    //fonction qui gère l'affichage du jeu
    DrawBoard(&game->board);
    DrawEntity(&game->player, &game->board);

    for (int i = 0 ; i < game->enemyAliveCount ; i++){
        DrawEntity(&game->enemies[i], &game->board);
    }
}

void HandleKey(Game *game, int key){
    //Pour gérer les inputs du clavier et agir en conséquence.
    //Finalement on transmet un déplacement dans la matrice du plateau plus qu'une position absolue.
    switch (key)
    {
    case KEY_UP:
        UpdateEntity(&game->player, game, &game->board, (Vector2){-1,0});
        break;
    case KEY_DOWN:
        UpdateEntity(&game->player, game, &game->board,(Vector2){1,0});
        break;
    case KEY_LEFT:
        UpdateEntity(&game->player, game, &game->board,(Vector2){0,-1});
        break;
    case KEY_RIGHT:
        UpdateEntity(&game->player, game, &game->board,(Vector2){0,1});
        break;
    case KEY_SPACE :
        Explosion(game, game->player.pos, 2) ;
        break;
    }
}

void AddEnnemi(Game *game, Vector2 V){
    if (game->enemyAliveCount < 10){

        Texture2D mob1 = LoadTexture("assets/character2.png");
        InitEntity(&game->enemies[game->enemyAliveCount], V, 1, &mob1, ENTITY_ENEMY);

        game->enemyAliveCount++ ;
    }
}



//savoir si la case est innocupé
bool IsEmpty(Game *game, Vector2 V){
    for( int i = 0 ; i < game->enemyAliveCount ; i++){
        if (game->enemies[i].pos.x == V.x && game->enemies[i].pos.y == V.y){ return false ;}
    }
    //en l'absence d'obstacles
    //joueur
    return ! (game->player.pos.x == V.x && game->player.pos.y == V.y)  ;
}

//récupère l'adresse d'une entité sur une case donné
Entity* ENtityAt(Game *game, Vector2 V){
    for( int i = 0 ; i < game->enemyAliveCount ; i++){
        if (game->enemies[i].pos.x == V.x && game->enemies[i].pos.y == V.y){ return &game->enemies[i] ;}
    }
    if(game->player.pos.x == V.x && game->player.pos.y == V.y){return &game->player ;}
    return NULL ;
}


//donne le nombre de cases maximum concerné par un rayon
int GetArea(int size){
    if( size == 0){return 1;}
    return GetArea(size-1) + 4*size ;
}


void Explosion(Game *game, Vector2 V, int radius){
    dataMove D ;
    createDataMouv(radius, &D) ;

    FindZone(game, &D, (int) V.x, (int) V.y, GetArea(radius) , radius) ;

    for(int pos = 0 ; pos < D.cursor_a ; pos++){
        if ( ! IsEmpty(game, D.acces[pos])){
            printf("entite trouve \n");
            Push(game, V, D.acces[pos]) ;
        }
    }
    free(D.known);
    free(D.acces);
    free(D.next);
}

//pousse une personnage
void Push(Game *game, Vector2 origin, Vector2 aim){
    Vector2 direction = (Vector2){0,0} ;
    if( ( ENtityAt(game, aim) ) != NULL){

        if(origin.x > aim.x){ direction.x-- ;}
        if(origin.x < aim.x){ direction.x++ ;}
        if(origin.y > aim.y){ direction.y-- ;}
        if(origin.y < aim.y){ direction.y++ ;}

        UpdateEntity(ENtityAt(game, aim), game, &game->board, direction) ;
    }
}




//init tout a 0
void createDataMouv(int radius, dataMove *D) {
    int area = GetArea(radius) ;
    D->acces = NULL ;
    D->known = NULL ;
    D->next = NULL ;

    initAcces(area, D);    
    initKnown(area, D);   
    initNext(area , D);   
}



//remet a zéro les listes de vecteur (cases)
void initAcces(int area, dataMove *D){
    free(D->acces);
    D->acces = calloc( area, sizeof(Vector2) ) ;
    for (int i = 0 ; i < area ; i++){
        D->acces[i].x = -1 ;
        D->acces[i].y = -1 ;
    }
    D->cursor_a = 0 ;
}

void initKnown(int area, dataMove *D){
    free(D->known);
    D->known = calloc( area*4 , sizeof(Vector2) ) ;
    for (int i = 0 ; i < area *4; i++){
        D->known[i].x = -1 ;
        D->known[i].y = -1 ;
    }
    D->cursor = 0 ;
}

void initNext(int area,dataMove *D){
    free(D->next);
    D->next = calloc( area*4, sizeof(Vector2) ) ;
    for (int i = 0 ; i < area*4 ; i++){
        D->next[i].x = -1 ;
        D->next[i].y = -1 ;
    }
    D->cursor_n = 0 ;
}



//ajout d'un vecteur dans la liste
void addKnown(dataMove *D, int x, int y, int cap){
    if (D->cursor < cap*4){
        D->known[D->cursor].x = x ;
        D->known[D->cursor].y = y ;
        D->cursor++ ;
    }
}

void addAcces(dataMove *D, int x, int y, int cap){
    if (D->cursor_a < cap){
        D->acces[D->cursor_a].x = x ;
        D->acces[D->cursor_a].y = y ;
        D->cursor_a++ ;
    }
}

void addNext(dataMove *D, int x, int y, int cap){
    if (D->cursor_n < cap*4){
        D->next[D->cursor_n].x = x ;
        D->next[D->cursor_n].y = y ;
        D->cursor_n++ ;
}}



//regarde si un vecteur est dans une liste
int isIn(Vector2 * liste, int size, int x, int y){
    for (int i = 0 ; i < size ; i++){
        if(liste[i].x  == x && liste[i].y == y){
            return 1 ; //true : exploré
        }
    }
    return 0 ; //defaut
}


//a partir d'une position vérifie si c'est une case accessible ajout les cases adjacent dans la liste de celles a regarder
void AddZone(Game *game, dataMove *D, int x, int y, int area){
    
    if (! (x > -1 && x < game->board.width && y > -1 && y < game->board.height) ){ //déborde
        return ;
    }
    //hors plateau

    if ( isIn(D->acces, D->cursor_a, x, y) ){
        return ;
    }
    //deja traversé
    addAcces(D, x, y, area) ;
    

    addNext(D, x-1, y, area) ;
    addNext(D, x+1, y, area) ;
    addNext(D, x, y-1, area) ;
    addNext(D, x, y+1, area) ;
    //sans obstacles
}


void FindZone(Game *game, dataMove *D, int x, int y, int area, int radius){ 

    AddZone(game, D, x, y, area) ;
    

    for (int i = 0 ; i < radius ; i++ ){
        //déplace la liste pour qu'elle ne soit pas modifier quand on ajouter les elements suivants
        initKnown(area, D) ;
        for (int elem = 0 ; elem < D->cursor_n ; elem++){
            addKnown(D, D->next[elem].x , D->next[elem].y, area) ;
        }

        initNext( area , D); 

        //parcours la liste présente
        for (int n = 0 ; n < D->cursor ; n++){
            AddZone(game, D, D->known[n].x , D->known[n].y, area ) ;
            //ajout des elements
        }
    }
}


        