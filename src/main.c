#include "raylib.h"
#include "game.h"
#include "menu.h"
#include "raylib.h"

int main(void)
{
    //Ouverture de la fenêtre :
    InitWindow(1920, 1080, "Projet L2 info");
    InitAudioDevice(); 

    float volume = 0.05f; //Valeur temporaire pour le bien de mon ouïe.
    Music music = LoadMusicStream("assets/atlasaudio-ambient-cinematic-510518.mp3");
    Game game;
    Menu menu;

    SetTargetFPS(60);
    SetExitKey(KEY_NULL);
    InitGame(&game);
    InitMenu(&menu);
    SetMusicVolume(music, volume);
    PlayMusicStream(music);    

    //Game loop.
    while (!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(SKYBLUE);
        switch (game.state){
        case GAME:
            UpdateGame(&game);
            DrawGame(&game);
            break;
        case MENU:
            updateMenu(&menu, &game);
            DrawMenu(&menu);
            break;
        }
        
        UpdateMusicStream(music);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}