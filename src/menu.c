#include "menu.h"
#include "button.h"

void InitMenu(Menu *menu){

    Texture2D startTexture = LoadTexture("assets/start.png");
    Texture2D settingsTexture = LoadTexture("assets/settings.png");
    Texture2D quitTexture = LoadTexture("assets/quit.png");

    InitButton(&menu->startButton, ((GetScreenWidth()/2)-(startTexture.width/2)),200, startTexture);
    InitButton(&menu->SettingsButton, ((GetScreenWidth()/2)-(settingsTexture.width/2)),((GetScreenHeight()/2)-(settingsTexture.height/2)), settingsTexture);
    InitButton(&menu->quitButton,((GetScreenWidth()/2)-(quitTexture.width/2)), 675, quitTexture);

}

void DrawMenu(Menu *menu){
    BeginDrawing();         
    ClearBackground((Color){160, 227, 253, 255});
    DrawButton(&menu->startButton);
    DrawButton(&menu->SettingsButton);
    DrawButton(&menu->quitButton);
    EndDrawing();
}