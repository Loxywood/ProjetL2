#include "board.h"
#include "raylib.h"
#include <stdlib.h>
//Initialisation du plateau de jeu.
void BoardInit(Board *board, int width, int height, float scale){
    //
    board->width = width;
    board->height = height;
    board->startX = GetScreenWidth()/2;
    board->startY = GetScreenHeight()/10;
    board->tile_scale = scale;
    //
    board->tiles = (Tile**)malloc(board->width * sizeof(Tile*));
        for(int i = 0; i < board->width; i++){
        board->tiles[i] = (Tile*)malloc(board->height * sizeof(Tile));
    }
    //
    Texture2D grass_texture = LoadTexture("assets/grass_tile_crop.png"); //Texture par défaut, à remplacer plus tard.
    //
    for(int i=0;i<board->width;i++){
        for(int j=0;j<board->height;j++){

            float posX = (board->startX)+(j-i)*(board->tile_scale)*(grass_texture.width / 2.0f);
            float posY = board->startY+(j+i)*board->tile_scale*(grass_texture.height / 4.0f);
            InitTile(&board->tiles[i][j], grass_texture, posX, posY); //Initialisation de chaque tuile avec la texture et les positions.
        }
    }
}

//Dessin du plateau de jeu.
void DrawBoard(Board *board){
    for(int i=0;i<board->width;i++){
        for(int j=0;j<board->height;j++){
            DrawTile(&board->tiles[i][j], board->tile_scale);
        }
    }
}