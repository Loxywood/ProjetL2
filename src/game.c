#include "game.h"
#include "raylib.h"
#include <math.h>
#include <stddef.h>
#include <stdlib.h>

#define GAME_SCALE 0.3f

void InitGame(Game *game) {
    BoardInit(&game->board, 10, 10, GAME_SCALE);

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
}

void HandleKey(Game *game, int key){
    //Pour gérer les inputs du clavier et agir en conséquence.
    //Finalement on transmet un déplacement dans la matrice du plateau plus qu'une position absolue.
    switch (key)
    {
    case KEY_UP:
        UpdateEntity(&game->player,&game->board,(Vector2){-1,0});
        break;
    case KEY_DOWN:
        UpdateEntity(&game->player,&game->board,(Vector2){1,0});
        break;
    case KEY_LEFT:
        UpdateEntity(&game->player,&game->board,(Vector2){0,-1});
        break;
    case KEY_RIGHT:
        UpdateEntity(&game->player,&game->board,(Vector2){0,1});
        break;
    }
}

//savoir si la case est innocupé
bool IsEmpty(Game *game, Vector2 V){
    for( int i = 0 ; i < game->enemyAliveCount ; i++){
        if (game->enemies[i].pos.x == V.x && game->enemies[i].pos.y == V.y){ return false ;}
    }
    //en l'absence d'obstacles
    return game->player.pos.x == V.x && game->player.pos.y == V.y ;
}


//récupère l'entité sur une case donné (pourrais y ajouter une fonction)
Entity* Affected(Game *game, Vector2 V){
    for( int i = 0 ; i < game->enemyAliveCount ; i++){
        if (game->enemies[i].pos.x == V.x && game->enemies[i].pos.y == V.y){ return &game->enemies[i] ;}
    }
    if(game->player.pos.x == V.x && game->player.pos.y == V.y){return &game->player ;}
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
            Entity* E = Affected(game, D.acces[pos]) ;
            //ici on mettra l'effet //ou on passera la fonction dans le Affected
        }
    }
}




//init tout a 0
void createDataMouv(int radius, dataMove *D) {
    int area = GetArea(radius) ;
    initAcces(area, D);    
    initKnown(area, D);   
    initNext( (4*(1+radius) > area) ? 4*(1+radius) : area , D);   
    //il faut prendre le plus grand des deux mais j'optimise
}



//remet a zéro les listes de vecteur (cases)
void initAcces(int area, dataMove *D){
    D->acces = calloc( area, sizeof(Vector2) ) ;
    for (int i = 0 ; i < area ; i++){
        D->acces[i].x = -1 ;
        D->acces[i].y = -1 ;
    }
    D->cursor_a = 0 ;
}

void initKnown(int area, dataMove *D){
    D->known = calloc( area, sizeof(Vector2) ) ;
    for (int i = 0 ; i < area ; i++){
        D->known[i].x = -1 ;
        D->known[i].y = -1 ;
    }
    D->cursor = 0 ;
}

void initNext(int area,dataMove *D){
    D->next = calloc( area, sizeof(Vector2) ) ;
    for (int i = 0 ; i < area ; i++){
        D->next[i].x = -1 ;
        D->next[i].y = -1 ;
    }
    D->cursor_n = 0 ;
}



//ajout d'un vecteur dans la liste
void addKnown(dataMove *D, int x, int y){
    D->known[D->cursor].x = x ;
    D->known[D->cursor].y = y ;
    D->cursor++ ;
}

void addAcces(dataMove *D, int x, int y){
    D->acces[D->cursor_a].x = x ;
    D->acces[D->cursor_a].y = y ;
    D->cursor_a++ ;
}

void addNext(dataMove *D, int x, int y){
    D->next[D->cursor_n].x = x ;
    D->next[D->cursor_n].y = y ;
    D->cursor_n++ ;
}



//regarde si un vecteur est dans une liste
int isIn(Vector2 * liste, int size, int x, int y){

    for (int i = 0 ; i < size ; i++){
        if (liste[i].x  == -1 && liste[i].y == -1 ) {
            return 0 ; //false : innexploré
        }
        else if(liste[i].x  == x && liste[i].y == y){
            return 1 ; //true : exploré
        }
    }
    return 0 ; //defaut
}


//a partir d'une position vérifie si c'est une case accessible ajout les cases adjacent dans la liste de celles a regarder
void AddZone(Game *game, dataMove *D, int x, int y){
    
    if (! (x > -1 && x < game->board.width && y > -1 && y < game->board.height) ){ //déborde
        return ;
    }
    //hors plateau

    if ( isIn(D->acces, D->cursor_a, x, y) ){
        return ;
    }
    //deja traversé
    addAcces(D, x, y) ;

    addNext(D, x-1, y) ;
    addNext(D, x+1, y) ;
    addNext(D, x, y-1) ;
    addNext(D, x, y+1) ;
    //sans obstacles
}


void FindZone(Game *game, dataMove *D, int x, int y, int area, int radius){ 

    AddZone(game, D, x, y) ;
    initKnown(area, D) ;

    for (int i = 0 ; i < radius ; i++ ){
        //déplace la liste pour qu'elle ne soit pas modifier quand on ajouter les elements suivants
        for (int elem = 0 ; elem < D->cursor_n ; elem++){
            D->known[elem] = D->next[elem] ;
        }
        D->cursor = D->cursor_n ;

        initNext( (4*(1+radius) > area) ? 4*(1+radius) : area , D); 

        //parcours la liste présente
        for (int n = 0 ; n < D->cursor ; n++){
            AddZone(game, D, D->known[n].x , D->known[n].y ) ;
            //ajout des elements
        }
    }
}


        