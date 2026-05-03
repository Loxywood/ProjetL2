#include "menu.h"
#include "button.h"

void InitMenu(Menu *menu){

    Texture2D startTexture = LoadTexture("assets/start.png");
    Texture2D startHoverTexture = LoadTexture("assets/start_hovering.png");
    Texture2D settingsTexture = LoadTexture("assets/settings.png");
    Texture2D settingsHoverTexture = LoadTexture("assets/settings_hovering.png");
    Texture2D quitTexture = LoadTexture("assets/quit.png");
    Texture2D quitHoverTexture = LoadTexture("assets/quit_hovering.png");
    
    InitButton(&menu->buttons[0], GetScreenWidth() / 2 - startTexture.width / 2, GetScreenHeight() / 2 - startTexture.height - 10, startTexture);
    menu->buttons[0].textureHover = startHoverTexture;
    
    InitButton(&menu->buttons[1], GetScreenWidth() / 2 - settingsTexture.width / 2, GetScreenHeight() / 2, settingsTexture);
    menu->buttons[1].textureHover = settingsHoverTexture;
    
    InitButton(&menu->buttons[2], GetScreenWidth() / 2 - quitTexture.width / 2, GetScreenHeight() / 2 + quitTexture.height + 10, quitTexture);
    menu->buttons[2].textureHover = quitHoverTexture;

}

void updateMenu(Menu *menu){
    for (int i = 0; i < BUTTON_COUNT; i++){
        isHovering(&menu->buttons[i]);
    }
}

void DrawMenu(Menu *menu){
    BeginDrawing();         
    ClearBackground((Color){160, 227, 253, 255});

    for (int i = 0; i < BUTTON_COUNT; i++)
    {
        DrawButton(&menu->buttons[i]);
    }
    
    EndDrawing();
}