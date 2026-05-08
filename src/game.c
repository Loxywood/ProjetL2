
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

    game->sprite[0] = (Texture2D) LoadTexture("assets/pouch.png"); 
    game->sprite[1] = (Texture2D) LoadTexture("assets/pouch_stun.png"); 
    game->sprite[2] = (Texture2D) LoadTexture("assets/pouch_ready.png"); 

    game->sprite[3] = (Texture2D) LoadTexture("assets/sparchu.png"); 
    game->sprite[4] = (Texture2D) LoadTexture("assets/sparchu_stun.png"); 
    game->sprite[5] = (Texture2D) LoadTexture("assets/sparchu_ready.png"); 

    game->HPtexture = (Texture2D) LoadTexture("assets/heart.png"); 

    game->enemyAliveCount = 0 ;
    game->wallCount = 0 ;

    Texture2D mob1 = LoadTexture("assets/character.png");
    //Initialisation du héros;
    InitEntity(&game->player, (Vector2){0,0}, 3, &mob1, ENTITY_PLAYER);
    game->state = MENU;
}

void UpdateGame(Game *game){
    //fonction qui gère la logique du jeu
    HandleKey(game, GetKeyPressed());
}

void DrawGame(Game *game){
    //fonction qui gère l'affichage du jeu
    DrawBoard(&game->board);
    
    for (int j = 0 ; j < game->wallCount ; j++){
        DrawEntity(&game->walls[j], &game->board);
    }

    for (int i = 0 ; i < game->enemyAliveCount ; i++){
        DrawEntity(&game->enemies[i], &game->board);
    }
    
    DrawEntity(&game->player, &game->board);


    for (int hp = 0 ; hp < game->player.hp ; hp++){
        DrawTextureEx(game->HPtexture, (Vector2){10+(hp* 50),1}, 0.0, 0.3, WHITE);
    }

}

void HandleKey(Game *game, int key){
    //Pour gérer les inputs du clavier et agir en conséquence.
    //Finalement on transmet un déplacement dans la matrice du plateau plus qu'une position absolue.
    switch (key)
    {
    case KEY_UP:
        Move(game, game->player.pos, (Vector2){-1,0}, true);
        EnemiesTurn(game) ;
        break;
    case KEY_DOWN:
        Move(game, game->player.pos, (Vector2){1,0}, true);
        EnemiesTurn(game) ;
        break;
    case KEY_LEFT:
        Move(game, game->player.pos, (Vector2){0,-1}, true);
        EnemiesTurn(game) ;
        break;
    case KEY_RIGHT:
        Move(game, game->player.pos, (Vector2){0,1}, true);
        EnemiesTurn(game) ;
        break;
    case KEY_SPACE :
        Explosion(game, game->player.pos, 2, Push) ;
        break;
    }
}

//fais apparaitre un ennemie (a renommer en anglais)
void AddEnnemiPouch(Game *game, Vector2 V){
    if (game->enemyAliveCount < 10){
        InitEntity(&game->enemies[game->enemyAliveCount], V, 1, &game->sprite[0], ENTITY_POUCH);
        game->enemyAliveCount++ ;
    }
}

void AddEnnemiSparchu(Game *game, Vector2 V){
    if (game->enemyAliveCount < 10){
        InitEntity(&game->enemies[game->enemyAliveCount], V, 1, &game->sprite[3], ENTITY_SPARCHU);
        game->enemyAliveCount++ ;
    }
}


void AddWall(Game *game, Vector2 V){
    if (game->wallCount < 20){

        Texture2D wall = LoadTexture("assets/bolder.png");
        InitEntity(&game->walls[game->wallCount], V, 1, &wall, ENTITY_ENEMY);

        game->wallCount++ ;
    }
}

bool IsWall(Game *game, Vector2 V){
for( int i = 0 ; i < game->wallCount ; i++){
        if (game->walls[i].pos.x == V.x && game->walls[i].pos.y == V.y){ return true ;}
    }
    return false ;
}

bool IsInBound(Board *board, Vector2 pos){
    if (pos.x < 0){
        return false ;
    }else if (pos.x >= board->width){
        return false ;
    }else if (pos.y < 0){
        return false ;
    }else if (pos.y >= board->height){
        return false ;
    }
    return true ;
}

//savoir si la case est innocupé (ennemi ou player)
bool IsEmpty(Game *game, Vector2 pos, bool playerIncluded){
    
    for( int i = 0 ; i < game->enemyAliveCount ; i++){
        if (game->enemies[i].pos.x == pos.x && game->enemies[i].pos.y == pos.y){ return false ;}
    }
    //en l'absence d'obstacles
    //joueur
    if (playerIncluded){
        return ! (game->player.pos.x == pos.x && game->player.pos.y == pos.y)  ;
    }
    return true ;   
}

//récupère l'adresse d'une entité (ennemie ou player) sur une case donné
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


//repousse toutes les entité d'une zone vers l'exterieur (on peut faire un pointeur de fonction pour utiliser autre chose que push)
void Explosion(Game *game, Vector2 V, int radius, bool (*effect)(Game*, Vector2, Vector2)){
    dataMove D ;
    createDataMouv(radius, &D) ;

    FindZone(game, &D, (int) V.x, (int) V.y, GetArea(radius) , radius, true) ;

    for(int pos = 0 ; pos < D.cursor_a ; pos++){
        if ( ! IsEmpty(game, D.acces[pos], true)){
            effect(game, V, D.acces[pos]) ;
        }
    }
    free(D.known);
    free(D.acces);
    free(D.next);
}


//pousse une personnage (à partir de cases)



bool Push(Game *game, Vector2 origin, Vector2 aim){
    Vector2 direction = (Vector2){0,0} ;
    if( ( ENtityAt(game, aim) ) != NULL){

        if (origin.x == aim.x && origin.y == aim.y){ return true ;}

        if(origin.x > aim.x){ direction.x-- ;}
        if(origin.x < aim.x){ direction.x++ ;}
        if(origin.y > aim.y){ direction.y-- ;}
        if(origin.y < aim.y){ direction.y++ ;}

        bool succes = Move(game, aim, direction, true ) ;
        if (! succes){
            if (ENtityAt(game, aim)->coolDown > 0){
                Deals(game, origin, aim) ;
            }
            if( ( ENtityAt(game, aim) ) != NULL){
                GetStun(game, ENtityAt(game, aim)) ;
            }
        }
        return succes ;
    }
    return false ;
}

bool Move(Game * game, Vector2 origin, Vector2 dir, bool push){
    if (dir.x == 0  &&  0== dir.y){
        return false ;
    }

    Vector2 aim = (Vector2){origin.x + dir.x, origin.y + dir.y};
    if( ( ENtityAt(game, origin) ) != NULL){
        if( (! IsInBound(&game->board, aim)) || IsWall(game, aim)){
            return false ;
        } 

        if( !push ){
            if (! IsEmpty(game, aim, true)){ return false ;}
        }else{
            if( (! IsEmpty(game, aim, true)) && ! Push(game, origin, aim) ){ return false ;}
        }
        
        UpdateEntity(ENtityAt(game, origin), &game->board, dir) ;
    }
    return true ;
}

bool Deals(Game *game, Vector2 origin, Vector2 aim){
    Entity* target = ENtityAt(game, aim) ;
    if( target != NULL){

        target->hp-- ;
        if (target->hp <= 0){
            if( target != &game->player){
                EnemyDeath(game, aim) ;
                return true ;
            }
        }
        
    }
    return false ;

}

void EnemyDeath(Game *game, Vector2 pos){
    int index = 0 ;
    for (int i = 0 ; i < game->enemyAliveCount ; i++){
        if (game->enemies[i].pos.x == pos.x && game->enemies[i].pos.y == pos.y) {
            index = i ;
            break ;
        }
    }
    game->enemyAliveCount-- ;
    for (int enemy = index ; enemy < game->enemyAliveCount ; enemy++){
        game->enemies[enemy] = game->enemies[enemy+1] ;
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


//-1 -1 n'est pas atteignable et ne sera pas lu tant que les fonctions concernées sont utilisé
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
int IsIn(Vector2 * liste, int size, int x, int y){
    for (int i = 0 ; i < size ; i++){
        if(liste[i].x  == x && liste[i].y == y){
            return 1 ; //true : exploré
        }
    }
    return 0 ; //defaut
}


//a partir d'une position vérifie si c'est une case accessible ajout les cases adjacent dans la liste de celles a regarder
void AddZone(Game *game, dataMove *D, int x, int y, int area, bool trough){

    //hors plateau
    if (! (x > -1 && x < game->board.width && y > -1 && y < game->board.height) ){
        return ;
    }
    
    //deja traversé
    if ( IsIn(D->acces, D->cursor_a, x, y) ){
        return ;
    }

    //case prise par une entité ou un mur dans le cas d'une interdiction de passer a travers (pour mob)
    if ( (! trough) && ( (! IsEmpty(game, (Vector2){x,y}, false) ) || IsWall(game, (Vector2){x,y} ) ) ){
        return ;
    }

    
    addAcces(D, x, y, area) ;
    

    addNext(D, x-1, y, area) ;
    addNext(D, x+1, y, area) ;
    addNext(D, x, y-1, area) ;
    addNext(D, x, y+1, area) ;
    //sans obstacles
}


void FindZone(Game *game, dataMove *D, int x, int y, int area, int radius, bool trough){ 

    addAcces(D, x, y, area) ;
    

    addNext(D, x-1, y, area) ;
    addNext(D, x+1, y, area) ;
    addNext(D, x, y-1, area) ;
    addNext(D, x, y+1, area) ;
    

    for (int i = 0 ; i < radius ; i++ ){
        //déplace la liste pour qu'elle ne soit pas modifier quand on ajouter les elements suivants
        initKnown(area, D) ;
        for (int elem = 0 ; elem < D->cursor_n ; elem++){
            addKnown(D, D->next[elem].x , D->next[elem].y, area) ;
        }

        initNext( area , D); 

        //parcours la liste présente
        for (int n = 0 ; n < D->cursor ; n++){
            AddZone(game, D, D->known[n].x , D->known[n].y, area, trough ) ;
            //ajout des elements
        }
    }
}

Vector2* GetPath(Game* game, Vector2 pos, Vector2 aim, int length){

    if ((pos.x == aim.x) && (pos.y == aim.y)){
        return &(Vector2){0,0} ;
    }
    if (length == 0){ return NULL ;}


    Vector2 next ;
    Vector2 choices[4] ; 
    ListDir(choices) ;

    for( int i = 0 ; i < 4 ; i++ ){
        next = (Vector2){pos.x + choices[i].x, pos.y +choices[i].y}  ;
        if ( IsInBound(&game->board, next) && IsEmpty(game, next, false) && (! IsWall(game, next )) ){
            if (GetPath(game, next, aim, length -1) != NULL){
                printf("trouve\n") ;
                return &(Vector2){choices[i].x, choices[i].y} ;
            }
        }
    }
    return NULL ;
}


Vector2 SimplePath(Game *game, Vector2 pos, Vector2 aim){
    dataMove D ;

    for (int radius = 1 ; radius < 5 ; radius++){

        createDataMouv(radius, &D) ;
        
        FindZone(game, &D, (int) pos.x, (int) pos.y, GetArea(radius) , radius, false) ;

        if( IsIn( D.acces, D.cursor_a, (int) aim.x, (int) aim.y )){
            printf("find\n") ;
            Vector2 result = *GetPath(game, pos, aim, radius) ;
            free(D.known);
            free(D.acces);
            free(D.next);
            
            if(radius == 1 && ENtityAt(game, pos)->ready == 0){
                GetReady(game, ENtityAt(game, pos));
                return (Vector2){0,0} ;
            }

            return result ;
        }
    }
    printf("not found\n") ;
    free(D.known);
    free(D.acces);
    free(D.next);
    
    return RandomDir(game, pos) ;
}

Vector2 RandomDir(Game * game, Vector2 pos){
    int nb_dir = 0 ;
    Vector2 choices[4] ; 
    ListDir(choices) ;
    Vector2 aim ; 

    for( int i = 0 ; i < 4 ; i++ ){
        aim = (Vector2){pos.x + choices[i].x, pos.y +choices[i].y}  ;

        if ( IsInBound(&game->board, aim) && IsEmpty(game, aim , true) && (! IsWall(game, aim )) ){
            choices[nb_dir] = choices[i] ;
            nb_dir++ ;
        }
    }
    int S = rand() %(nb_dir) ;
    Vector2 V = choices[S] ;
    return V ;

}


void EnemiesTurn(Game* game){
    for( int i = 0 ; i < game->enemyAliveCount ; i++){
        if(game->enemies[i].coolDown > 0 ){
            GetBetter(game, &game->enemies[i]) ;
        }
        else if (game->enemies[i].ready)
        {
            switch (game->enemies[i].type)
            {
            case ENTITY_POUCH:
                Attack(game, &game->enemies[i]) ;
                break;
            
            case ENTITY_SPARCHU:
                Dash(game,  &game->enemies[i]) ;
                break;
            }
            
        }
        
        else{
            Move(game, game->enemies[i].pos, SimplePath(game, game->enemies[i].pos, game->player.pos), false )  ;
        }
    }
}
        

void ListDir(Vector2 * dir){
    dir[0] = (Vector2){0,1} ;
    dir[1] = (Vector2){0,-1} ;
    dir[2] = (Vector2){1,0} ;
    dir[3] = (Vector2){-1,0} ;
}