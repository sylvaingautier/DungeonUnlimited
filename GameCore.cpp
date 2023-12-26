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
    m_Environnement.initEnvironnements();
}

void GameCore::endGameCore()
{
    raylib::CloseWindow();          // Close window and OpenGL context
}

void GameCore::loopGameCore()
{
    // Main game loop
    bool affiche_grille = true;
    while (!raylib::WindowShouldClose())    // Detect window close button or ESC key
    {
        //----------------------------------------------------------------------------------

  // Draw
  //----------------------------------------------------------------------------------
        raylib::BeginDrawing();

        raylib::ClearBackground(raylib::BLACK);
        if (raylib::IsKeyDown(raylib::KEY_DOWN)) affiche_grille=false;
        if (raylib::IsKeyDown(raylib::KEY_UP)) affiche_grille=true;

        raylib::DrawTexture(m_Environnement.texture, 0, 0, raylib::WHITE);
        for (int x = 0; x < 24; x++)
        {
            for (int y = 0; y < 12; y++)
            {
                if (affiche_grille == true)
                {
                    raylib::DrawRectangleLines(x * 48, y * 48, 48, 48, raylib::GRAY);
                }
                    raylib::DrawText(raylib::TextFormat("%d", x+y*24), (x*48)+5, (y*48)+5, 10, raylib::WHITE);
            }
        }




        raylib::EndDrawing();
    }
}
