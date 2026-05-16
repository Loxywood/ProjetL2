
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
    game->turn = 0 ;
    game->start = 0 ;
    game->on = 1 ;
    game->speed = 1 ;

    game->sprite[0] = (Texture2D) LoadTexture("assets/pouch.png"); 
    game->sprite[1] = (Texture2D) LoadTexture("assets/pouch_stun.png"); 
    game->sprite[2] = (Texture2D) LoadTexture("assets/pouch_ready.png"); 

    game->sprite[3] = (Texture2D) LoadTexture("assets/sparchu.png"); 
    game->sprite[4] = (Texture2D) LoadTexture("assets/sparchu_stun.png"); 
    game->sprite[5] = (Texture2D) LoadTexture("assets/sparchu_ready.png"); 

    game->sprite[6] = (Texture2D) LoadTexture("assets/BOSS.png"); 

    game->sprite[7] = (Texture2D) LoadTexture("assets/character.png");

    game->sprite[8] = (Texture2D) LoadTexture("assets/Wall.png");

    game->HPtexture = (Texture2D) LoadTexture("assets/heart.png"); 

    game->enemyAliveCount = 0 ;
    game->wallCount = 0 ;
    //Initialisation du héros;
    game->state = MENU;

    InitLevel1(game) ;
}

void InitLevel1(Game *game){
    InitEntity(&game->player, (Vector2){0,0}, 3, &game->sprite[7], ENTITY_PLAYER);
    game->wallCount = 0 ; 
    
    AddWall(game, (Vector2){2,6}) ;
    AddWall(game, (Vector2){2,7}) ;
    AddWall(game, (Vector2){3,6}) ;
    AddWall(game, (Vector2){3,7}) ;

    AddWall(game, (Vector2){3,3}) ;
    AddWall(game, (Vector2){3,4}) ;
    AddWall(game, (Vector2){4,4}) ;
    AddWall(game, (Vector2){4,3}) ;

    AddWall(game, (Vector2){6,2}) ;
    AddWall(game, (Vector2){6,3}) ;
    AddWall(game, (Vector2){7,2}) ;
    AddWall(game, (Vector2){7,3}) ;

    AddWall(game, (Vector2){6,6}) ;
    AddWall(game, (Vector2){7,6}) ;
    AddWall(game, (Vector2){7,7}) ;
    AddWall(game, (Vector2){6,7}) ;

    AddEnnemiSparchu(game, (Vector2){5,6}) ;
    AddEnnemiSparchu(game, (Vector2){6,4}) ;

    game->NextLevel = InitLevel2 ;
    
}

void InitLevel2(Game *game){

    InitEntity(&game->player, (Vector2){0,0}, 3, &game->sprite[7], ENTITY_PLAYER);
    game->wallCount = 0 ; 
    
    for( int i = 0 ; i < 8 ; i++){
        AddWall(game, (Vector2){i,2}) ;
    }

    for( int i = 2 ; i < 6 ; i++){
        AddWall(game, (Vector2){i,4}) ;
    }

    for( int i = 2 ; i < 8 ; i++){
        AddWall(game, (Vector2){i,7}) ;
    }

    for( int i = 3 ; i < 7 ; i++){
        AddWall(game, (Vector2){7,i}) ;
    }

    AddWall(game, (Vector2){2,5}) ;
    AddWall(game, (Vector2){2,6}) ;

    

    AddEnnemiSparchu(game, (Vector2){4,0}) ;
    AddEnnemiSparchu(game, (Vector2){9,5}) ;
    AddEnnemiSparchu(game, (Vector2){1,4}) ;
    AddEnnemiSparchu(game, (Vector2){5,8}) ;

    AddEnnemiPouch(game, (Vector2){4,5}) ;

    game->NextLevel = InitLevel3 ;  
}

void InitLevel3(Game *game){
    InitEntity(&game->player, (Vector2){4,6}, 3, &game->sprite[7], ENTITY_PLAYER);
    game->wallCount = 0 ; 
    
    
    for( int i = 1 ; i < 9 ; i++ ){
        if (i != 3 && i != 6){
            AddWall(game, (Vector2){i,1}) ;
        }
    } 
    AddWall(game, (Vector2){4,0}) ;
    AddWall(game, (Vector2){5,0}) ;

    for( int i = 0 ; i < 10 ; i++ ){
        if (i != 2 && i != 4 && i != 5 && i != 7){
            AddWall(game, (Vector2){i,3}) ;
        }
    } 

    for( int i = 0 ; i < 10 ; i++ ){
        if (i != 2  && i != 7){
            AddWall(game, (Vector2){i,5}) ;
        }
    } 

    AddWall(game, (Vector2){3,4}) ;
    AddWall(game, (Vector2){6,4}) ;

    for( int i = 1 ; i < 9 ; i++ ){
        if (i != 3 && i != 6){
            AddWall(game, (Vector2){i,7}) ;
        }
    } 

    AddWall(game, (Vector2){2,8}) ;
    AddWall(game, (Vector2){7,8}) ;

    AddWall(game, (Vector2){4,9}) ;
    AddWall(game, (Vector2){5,9}) ;



    AddEnnemiSparchu(game, (Vector2){4,3}) ;
    AddEnnemiSparchu(game, (Vector2){4,4}) ;
    AddEnnemiSparchu(game, (Vector2){5,4}) ;
    AddEnnemiSparchu(game, (Vector2){5,3}) ;

    AddEnnemiPouch(game, (Vector2){1,8}) ;
    AddEnnemiPouch(game, (Vector2){8,8}) ;

    game->NextLevel = InitLevel4 ;
    
}

void InitLevel4(Game *game){
    InitEntity(&game->player, (Vector2){4,4}, 3, &game->sprite[7], ENTITY_PLAYER);
    game->wallCount = 0 ; 
    
    AddWall(game, (Vector2){2,6}) ;

    for( int i = 1 ; i < 9 ; i++ ){
        AddWall(game, (Vector2){i,1}) ;
    } 

    for( int i = 1 ; i < 9 ; i++ ){
        if(i != 4){
            AddWall(game, (Vector2){i,8}) ;
        }
    } 

    for( int i = 3 ; i < 7 ; i++ ){
        if(i != 4){
            AddWall(game, (Vector2){i,3}) ;
            AddWall(game, (Vector2){i,5}) ;
        }
    }
    AddWall(game, (Vector2){3,6}) ;
    AddWall(game, (Vector2){5,6}) ;

    for( int i = 2 ; i < 8 ; i++ ){
        AddWall(game, (Vector2){1,i}) ;
    }

    for( int i = 2 ; i < 8 ; i++ ){
        if(i != 4){
            AddWall(game, (Vector2){8,i}) ;
        }
    }

    AddEnnemiSparchu(game, (Vector2){0,0}) ;
    AddEnnemiSparchu(game, (Vector2){2,2}) ;
    AddEnnemiSparchu(game, (Vector2){7,7}) ;

    AddEnnemiPouch(game, (Vector2){8,4}) ;
    AddEnnemiPouch(game, (Vector2){4,8}) ;


    game->NextLevel = InitLevel5 ;
    
}

void InitLevel5(Game *game){
    InitEntity(&game->player, (Vector2){0,0}, 3, &game->sprite[7], ENTITY_PLAYER);
    game->wallCount = 0 ; 
    
    AddWall(game, (Vector2){2,6}) ;
    AddWall(game, (Vector2){6,2}) ;

    AddWall(game, (Vector2){7,7}) ;

    AddWall(game, (Vector2){0,9}) ;
    AddWall(game, (Vector2){9,0}) ;

    for(int i = 3 ; i < 8 ; i++){
        if (i != 6){
            AddWall(game, (Vector2){i,8}) ;
            AddWall(game, (Vector2){8,i}) ;
        }
    }

    for(int i = 0 ; i < 5 ; i++){
        if (i != 2){
            AddWall(game, (Vector2){i,3}) ;
            if(i != 3){
                AddWall(game, (Vector2){3,i}) ;
            }
        }
    }

    AddEnnemiBoss(game, (Vector2){5,5}) ;

    game->NextLevel = win ;
    
}

void win(Game * game){

}

void GameTime(Game* game){
        game->start = 0 ;
        game->turn = ( game->turn +1)  % (game->enemyAliveCount+1 ) ;
}

void UpdateGame(Game *game){
    //fonction qui gère la logique du jeu
    HandleKey(game, GetKeyPressed());
    game->start ++ ;
    EnemiesTurn(game) ;

    if(game->enemyAliveCount == 0){
        game->NextLevel(game) ;
    }
}

void DrawGame(Game *game){
    //fonction qui gère l'affichage du jeu
    DrawBoard(&game->board);
    
    //mur en fond
    for (int j = 0 ; j < game->wallCount ; j++){
        DrawEntity(&game->walls[j], &game->board);
    }

    //ennemies
    for (int i = 0 ; i < game->enemyAliveCount ; i++){
        DrawEntity(&game->enemies[i], &game->board);
    }
    
    //joueur
    DrawEntity(&game->player, &game->board);

    //munitionsr
    char message[3] ;
    sprintf(message, "%d", game->player.ready);
    DrawText(message, 250, 300, 50, BLACK) ;

    //coeurs
    for (int hp = 0 ; hp < game->player.hp ; hp++){
        DrawTextureEx(game->HPtexture, (Vector2){10+(hp* 50),1}, 0.0, 0.3, WHITE);
    }

    //defaite
    if(game->player.hp < 1){
        game->turn = 0 ;
        const char* message = "DEFAITE" ;
        DrawText(message, 250, 300, 350, BLACK) ;
        //coordonnées a changer
    }

    if(game->enemyAliveCount < 1){
        game->turn = 0 ;
        const char* message = "Victoire" ;
        DrawText(message, 250, 300, 350, BLACK) ;
        //coordonnées a changer
    }


}

void HandleKey(Game *game, int key){
    //Pour gérer les inputs du clavier et agir en conséquence.
    //Finalement on transmet un déplacement dans la matrice du plateau plus qu'une position absolue.
    if (game->turn == 0 && game->start > game->speed && game->on == 1){
        switch (key)
        {
        case KEY_UP:
            PlayerTurn(game, &game->player, (Vector2){-1,0});
            break;

        case KEY_DOWN:
            PlayerTurn(game, &game->player, (Vector2){1,0});
            break;

        case KEY_LEFT:
            PlayerTurn(game, &game->player, (Vector2){0,-1});
            break;

        case KEY_RIGHT:
            PlayerTurn(game, &game->player,(Vector2){0,1}) ;
            break;

        case KEY_SPACE :
            if (game->player.ready > 0){
                Explosion(game, game->player.pos, 2, Push) ;
                game->player.ready-- ;
                PlayerTurn(game, &game->player,(Vector2){0,0}) ;
                
            }
            break;
        case KEY_ENTER :
            printf("%d\n", game->wallCount) ;
            game->enemyAliveCount = 0 ;
            break;
        }
    }
}

//essentiel du tour du joueur
void PlayerTurn(Game * game, Entity *player, Vector2 direction){
    if( player->coolDown == 2 ){
        player->ready++ ;
        player->coolDown = 0 ;
    }
    else{player->coolDown++ ;}

    Move(game, game->player.pos, direction, true);

    GameTime(game) ;
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

void AddEnnemiBoss(Game *game, Vector2 V){
    if (game->enemyAliveCount < 10){
        InitEntity(&game->enemies[game->enemyAliveCount], V, 3, &game->sprite[6], ENTITY_BOSS);
        game->enemyAliveCount++ ;
    }
}


void AddWall(Game *game, Vector2 V){
    if (game->wallCount < 40){

        
        InitEntity(&game->walls[game->wallCount], V, 1, &game->sprite[8], ENTITY_ENEMY);

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
    Entity *entity = ENtityAt(game, aim) ;
    if( ( entity ) != NULL){

        if (origin.x == aim.x && origin.y == aim.y){ return true ;}

        if(origin.x > aim.x){ direction.x-- ;}
        if(origin.x < aim.x){ direction.x++ ;}
        if(origin.y > aim.y){ direction.y-- ;}
        if(origin.y < aim.y){ direction.y++ ;}

        if( entity->type == ENTITY_BOSS){ return false ;}

        bool succes = Move(game, aim, direction, true ) ;
        if (! succes){
            if (entity->coolDown > 0){
                Deals(game, origin, aim) ;
            }
            if( ( entity ) != NULL){
                GetStun(game, entity) ;
            }
        }
        return succes ;
    }
    return false ;
}

bool Move(Game * game, Vector2 origin, Vector2 dir, bool push){
    if ( (dir.x == 0 )  && ( 0 == dir.y) ){
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
            else{ game->on = 0 ;}
        }
        
    }
    return false ;

}

void EnemyDeath(Game *game, Vector2 pos){
    int index = 0 ;


    for (int i = 0 ; i < game->enemyAliveCount ; i++){
        if (game->enemies[i].pos.x == pos.x && game->enemies[i].pos.y == pos.y) {
            index = i ;
            if (game->enemies[i].type == ENTITY_BOSS){
                dataMove D ;
                createDataMouv(2, &D) ;

                FindZone(game, &D, (int) game->enemies[i].pos.x, (int) game->enemies[i].pos.y, GetArea(2) , 2, true) ;

                for(int pos = 0 ; pos < D.cursor_a ; pos++){
                        TextureToGreen(&game->board, D.acces[pos].x, D.acces[pos].y) ;
                }
                free(D.known);
                free(D.acces);
                free(D.next);

                TextureToGreen(&game->board, 1, 4) ;
                TextureToGreen(&game->board, 8, 8) ;
                TextureToGreen(&game->board, 4, 1) ;
            }
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

//donne la direction a prendre
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
                return &(Vector2){choices[i].x, choices[i].y} ;
            }
        }
    }
    return NULL ;
}

//cherche un chemin (vision limite)
Vector2 SimplePath(Game *game, Vector2 pos, Vector2 aim){
    dataMove D ;

    for (int radius = 1 ; radius < 5 ; radius++){

        createDataMouv(radius, &D) ;
        
        FindZone(game, &D, (int) pos.x, (int) pos.y, GetArea(radius) , radius, false) ;

        if( IsIn( D.acces, D.cursor_a, (int) aim.x, (int) aim.y )){
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
    if (nb_dir == 0){ return (Vector2){0,0} ;}
    int S = rand() %(nb_dir) ;
    Vector2 V = choices[S] ;
    return V ;

}


void EnemiesTurn(Game* game){
    int i = game->turn ;
    i-- ;
    Entity *ennemy = &game->enemies[i] ;
    if ( i >= 0 && game->start > game->speed){

        if(ennemy->type == ENTITY_BOSS) {
            dataMove D ;
            switch (ennemy->coolDown)
            {
            
            case 0 :
            case 4 :
            case 8 :
                createDataMouv(2, &D) ;

                FindZone(game, &D, (int) ennemy->pos.x, (int) ennemy->pos.y, GetArea(2) , 2, true) ;

                for(int pos = 0 ; pos < D.cursor_a ; pos++){
                        TextureToRed(&game->board, D.acces[pos].x, D.acces[pos].y) ;
                }
                free(D.known);
                free(D.acces);
                free(D.next);
                break;
            
            case 1 :
            case 5 :
            case 9 :
                Attack(game, ennemy, 2) ;
                
                createDataMouv(2, &D) ;

                FindZone(game, &D, (int) ennemy->pos.x, (int) ennemy->pos.y, GetArea(2) , 2, true) ;

                for(int pos = 0 ; pos < D.cursor_a ; pos++){
                        TextureToGreen(&game->board, D.acces[pos].x, D.acces[pos].y) ;
                }
                free(D.known);
                free(D.acces);
                free(D.next);
                break;
            
            case 2 :
                TextureToRed(&game->board, 4,1) ;
                break;

            case 6 : 
                TextureToRed(&game->board, 1,4) ;
                break;

            case 10 : //trois d'un coup
                TextureToRed(&game->board, 8,8) ;
                TextureToRed(&game->board, 1,4) ;
                TextureToRed(&game->board, 4,1) ;
                break;


            case 3 :
                TextureToGreen(&game->board, 4,1) ;
                if(IsEmpty(game, (Vector2){4,1}, true)){
                    AddEnnemiSparchu(game, (Vector2){4,1}) ;
                    game->enemies[game->enemyAliveCount -1].coolDown ++ ;
                }
                else{
                    Deals(game, (Vector2){4,1}, (Vector2){4,1}) ;
                }
                break;

            case 7 : 
                TextureToGreen(&game->board, 1,4) ;
                if(IsEmpty(game, (Vector2){1,4}, true)){
                    AddEnnemiSparchu(game, (Vector2){1,4}) ;
                    game->enemies[game->enemyAliveCount -1].coolDown ++ ;
                }
                else{
                    Deals(game, (Vector2){1,4}, (Vector2){1,4}) ;
                }
                break;

            case 11 : //trois d'un coup

                TextureToGreen(&game->board, 1,4) ;
                if(IsEmpty(game, (Vector2){1,4}, true)){
                    AddEnnemiSparchu(game, (Vector2){1,4}) ;
                    game->enemies[game->enemyAliveCount -1].coolDown ++ ;
                }
                else{
                    Deals(game, (Vector2){1,4}, (Vector2){1,4}) ;
                }


                TextureToGreen(&game->board, 4,1) ;
                if(IsEmpty(game, (Vector2){4,1}, true)){
                    AddEnnemiSparchu(game, (Vector2){4,1}) ;
                    game->enemies[game->enemyAliveCount -1].coolDown ++ ;
                }
                else{
                    Deals(game, (Vector2){4,1}, (Vector2){4,1}) ;
                }

                TextureToGreen(&game->board, 5, 1) ;
                if(IsEmpty(game, (Vector2){5, 1}, true)){
                    AddEnnemiSparchu(game, (Vector2){5, 1}) ;
                    game->enemies[game->enemyAliveCount -1].coolDown ++ ;
                }
                else{
                    Deals(game, (Vector2){5, 1}, (Vector2){5, 1}) ;
                }
                break;


            default:
                break;
            }
            ennemy->coolDown = ( ennemy->coolDown +1 ) %12 ;










        }
        else if(ennemy->coolDown > 0 ){
            GetBetter(game, ennemy) ;
        }
        else if (ennemy->ready)
        {
            switch (game->enemies[i].type)
            {
            case ENTITY_SPARCHU :
                Attack(game, ennemy, 1) ;
                break;
            
            case ENTITY_POUCH :
                Dash(game,  ennemy) ;
                break;
            }
            
        }
        
        //si le joueur n'est pas detecté -> direction aléatoire
        else{
            Move(game, ennemy->pos, SimplePath(game, ennemy->pos, game->player.pos), false )  ;
        }
        GameTime(game) ;
    }
}
        

void ListDir(Vector2 * dir){
    dir[0] = (Vector2){0,1} ;
    dir[1] = (Vector2){0,-1} ;
    dir[2] = (Vector2){1,0} ;
    dir[3] = (Vector2){-1,0} ;
}