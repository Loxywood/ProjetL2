#include "board.h"

//Initialisation du plateau de jeu.
void BoardInit(Board *board, int width, int height){
    board->width = width;
    board->height = height;
    board->tiles = (Tile**)malloc(board->width * sizeof(Tile*));
    //C'est Copilot qui a généré cette ligne :
    //Allocation de la place nécéssaire pour stocker le tableau.
    for(int i = 0; i < board->width; i++){
        board->tiles[i] = (Tile*)malloc(board->height * sizeof(Tile));
    }

    Texture2D test_texture = LoadTexture("assets/floor_tile.png"); //Texture par défaut, à remplacer plus tard.
    for(int i=0;i<board->width;i++){
        for(int j=0;j<board->height;j++){
            InitTile(&board->tiles[i][j], test_texture, i*25, j*25); //Initialisation de chaque tuile avec la texture et les positions.
        }
    }
}

//Dessin du plateau de jeu.
void DrawBoard(Board *board){
    for(int i=0;i<board->width;i++){
        for(int j=0;j<board->height;j++){
            DrawTile(&board->tiles[i][j]);
        }
    }
}