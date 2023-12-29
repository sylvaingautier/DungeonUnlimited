#include "GameCore.h"


GameCore::GameCore()
{
}

void GameCore::initGameCore()
{
    // Initialization
    //---------------------------------------------------------
    raylib::InitWindow(SCREENWIDTH, SCREENHEIGHT, "Dongeon Random");
    raylib::SetTargetFPS(60);



}

void GameCore::endGameCore()
{
    raylib::CloseWindow();          // Close window and OpenGL context
}

void GameCore::loopGameCore()
{
    // Main game loop
    bool affiche_grille = true;
    bool affiche_tileset = false;
    raylib::Texture2D texture1;
    raylib::Texture2D texture2;
    raylib::Texture2D texture3;
    raylib::Vector2 map_pos_in_screen{};
    map_pos_in_screen.x = 0;
    map_pos_in_screen.y = 0;
    texture1 = LoadTextureFromImage(test.m_Environnement.m_Tileset);
    texture2 = LoadTextureFromImage(test.map[0]);
    texture3 = LoadTextureFromImage(test.map[1]);
    while (!raylib::WindowShouldClose())    // Detect window close button or ESC key
    {
        //----------------------------------------------------------------------------------

  // Draw
  //----------------------------------------------------------------------------------
        raylib::BeginDrawing();

        raylib::ClearBackground(raylib::BLACK);
        if (raylib::IsKeyDown(raylib::KEY_A)) affiche_grille=false;
        if (raylib::IsKeyDown(raylib::KEY_Z)) affiche_grille=true;
        if (raylib::IsKeyDown(raylib::KEY_T)) affiche_tileset = true;
        if (raylib::IsKeyDown(raylib::KEY_G)) affiche_tileset = false;
        if (raylib::IsKeyDown(raylib::KEY_UP)) map_pos_in_screen.y = map_pos_in_screen.y + 16;
        if (raylib::IsKeyDown(raylib::KEY_DOWN)) map_pos_in_screen.y = map_pos_in_screen.y - 16;
        if (raylib::IsKeyDown(raylib::KEY_RIGHT)) map_pos_in_screen.x = map_pos_in_screen.x + 16;
        if (raylib::IsKeyDown(raylib::KEY_LEFT)) map_pos_in_screen.x = map_pos_in_screen.x - 16;

        if (affiche_tileset == true)
        {
            raylib::DrawTexture(texture1, map_pos_in_screen.x, map_pos_in_screen.y, raylib::WHITE);
        }
        else
        {
            raylib::DrawTexture(texture2, map_pos_in_screen.x, map_pos_in_screen.y, raylib::WHITE);
            raylib::DrawTexture(texture3, map_pos_in_screen.x, map_pos_in_screen.y, raylib::WHITE);
        }
       
       if (affiche_tileset == true)
       {
           for (int x = 0; x < test.m_Environnement.m_sizeTileSet_x; x++)
           {
               for (int y = 0; y < test.m_Environnement.m_sizeTileSet_y; y++)
               {
                   if (affiche_grille == true)
                   {
                       raylib::DrawRectangleLines(x * 48, y * 48, 48, 48, raylib::GRAY);
                   }
                   raylib::DrawText(raylib::TextFormat("%d", x + y * 20), (x * 48) + 5, (y * 48) + 5, 10, raylib::WHITE);
               }
           }
       }



        raylib::EndDrawing();
    }
}
