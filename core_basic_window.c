#include "raylib.h"

#define SCREEN_WIDTH  1280
#define SCREEN_HEIGHT  720

#define CHARACTER_HEIGHT  SCREEN_HEIGHT/2

//Szöveg középre igazítása
void DrawTextCenter(const char *text, int fontSize, Color color)
{
   
    int textWidth = MeasureText(text, fontSize);

    DrawText(
         text,
         SCREEN_WIDTH / 2 - textWidth / 2,
         SCREEN_HEIGHT / 2 - fontSize / 2,
         fontSize,
         color
    );
}

void DrawCharacterCenter(Texture2D character){
    
   float width = (float)character.width;
   float height = (float)character.height;
   
   float characterScale = (float)CHARACTER_HEIGHT/(float)height;
   
   float x = SCREEN_WIDTH / 2.0f - (width * characterScale) / 2.0f;
   float y = SCREEN_HEIGHT / 2.0f - (height * characterScale) / 2.0f;
   
   //DrawText(TextFormat("szélesség: %f/ magasság: %f", width * characterScale, height * characterScale), 0, 0, 30, BLACK);   
   DrawTextureEx(character, (Vector2){x, y}, 0.0f, characterScale, WHITE);
}

int main (){
   
   //Képernyőablak létrehozása
   InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Super Mario");
   
   Texture2D character = LoadTexture("resources/textures/character/characterStand.png");
  
   if (!IsTextureValid(character)){
    CloseWindow();
    return 1;
   }
  
   SetTargetFPS(60);
   
   while (!WindowShouldClose())
   {
       BeginDrawing();
       
       ClearBackground(RAYWHITE);
       
       //Karakter kirajzolása középre
       DrawCharacterCenter(character);
       
       EndDrawing();
   }
   
   UnloadTexture(character);
   
   CloseWindow();

   return 0;

}