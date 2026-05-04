#include "raylib.h"
#include "game.h"
#include <stdio.h>

int main(void)
{
    //Ouverture de la fenêtre :
    InitWindow(1920, 1080, "Projet L2 info");
    InitAudioDevice(); 

    float volume = 0.05f; //Valeur temporaire pour le bien de mon ouïe.
    Music music = LoadMusicStream("assets/atlasaudio-ambient-cinematic-510518.mp3");
    Game game;

    SetTargetFPS(60);
    SetMusicVolume(music, volume);

    PlayMusicStream(music);
    
    InitGame(&game);
    

    //Game loop.
    while (!WindowShouldClose())
    {
        
        UpdateMusicStream(music);
        //UpdateGame(&game);
        
        BeginDrawing();         
        ClearBackground(SKYBLUE);

        

        UpdateGame(&game);
        DrawGame(&game);
        EndDrawing();
        
    }
    CloseWindow();
    return 0;
}