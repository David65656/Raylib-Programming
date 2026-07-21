#include "raylib.h"
#include <stdio.h>

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
   
   //Háttérzene inicializálása
   InitAudioDevice();
   
   //Háttérzene betöltése és lejátszása
   Music bgMusic = LoadMusicStream("resources/audio/music/music.wav");
   PlayMusicStream(bgMusic);
   
   //Textúrák betöltése
   Texture2D characterStand = LoadTexture("resources/textures/character/characterStand.png");
   Texture2D characterCrouch = LoadTexture("resources/textures/character/characterCrouch.png");
  
   if (!IsTextureValid(characterStand)){
    UnloadMusicStream(bgMusic);
    CloseAudioDevice();
    CloseWindow();
    return 1;
   }
   
   if (!IsTextureValid(characterCrouch)){
    UnloadMusicStream(bgMusic);
    CloseAudioDevice();
    CloseWindow();
    return 1;
   }
  
    //File megnyitása
    FILE *file = fopen("crouchTimes.txt", "w");
    if (file == NULL)
    {
        CloseAudioDevice();
        CloseWindow();
        return 1;
    }
  
    //Guggolás időpontjai és hozzá kapcsolódó változók
    float crouchTimes[] = {
        0.68f,
        0.92f,
        1.25f,
        1.42f,
        1.57f,
        1.93f,
        2.10f,
        2.27f,
        2.43f,
        2.60f,
        2.77f,
        3.10f,
        3.45f,
        3.85f,
        4.24f,
        4.44f,
        4.60f,
        4.97f,
        5.15f,
        5.34f,
        5.54f,
        5.72f,
        5.89f,
        6.24f
    };
    int i = 0;
    int beatCount = sizeof(crouchTimes) / sizeof(crouchTimes[0]);
  
   SetTargetFPS(60);
   
   while (!WindowShouldClose())
   {
       float t = GetMusicTimePlayed(bgMusic);
       if(t < 0.05f){
           i=0;
       }
       
       //Zene frissítése
       UpdateMusicStream(bgMusic);
       
       BeginDrawing();
       
       ClearBackground(RAYWHITE);
       
       //Beat-ek kigyűjtése
       if (IsKeyPressed(KEY_SPACE))
        fprintf(file, "%.2f\n", t);
        fflush(file);
       
       //Karakter kirajzolása középre
       if(i < beatCount &&
        t >= crouchTimes[i] &&
        t < crouchTimes[i] + 0.15f)
       {
          DrawCharacterCenter(characterCrouch);
       }
       else
       {
         DrawCharacterCenter(characterStand);
       }

       // Továbbléptetés guggolás után
       if(i < beatCount && t >= crouchTimes[i] + 0.15f)
       {
        i++;
       }

       
       EndDrawing();
   }
   
   //Textúrák felszabadítása
   UnloadTexture(characterStand);
   UnloadTexture(characterCrouch);
   
   //Zene leállítása
   UnloadMusicStream(bgMusic);
   CloseAudioDevice();
   
   //Fájl bezárása
   fclose(file);
   
   CloseWindow();

   return 0;

}
