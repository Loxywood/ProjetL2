#include "menu.h"
#include "button.h"

void InitMenu(Menu *menu){

    Texture2D startTexture = LoadTexture("assets/start.png");
    Texture2D settingsTexture = LoadTexture("assets/settings.png");
    Texture2D quitTexture = LoadTexture("assets/quit.png");

    InitButton(&menu->startButton, 100, 100, startTexture);
    InitButton(&menu->SettingsButton, 100, 200, settingsTexture);
    InitButton(&menu->quitButton, 100, 300, quitTexture);

}

void DrawMenu(Menu *menu){
    BeginDrawing();         
    ClearBackground(RAYWHITE);
    DrawButton(&menu->startButton);
    DrawButton(&menu->SettingsButton);
    DrawButton(&menu->quitButton);
    EndDrawing();
}