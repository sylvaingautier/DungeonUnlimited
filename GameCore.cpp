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
    TheDungeon.Init();
    hero.Init();
    hero.m_HeroPos.x = float(SCREENWIDTH / 2);
    hero.m_HeroPos.y = float(SCREENHEIGHT / 2);

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
    raylib::Texture2D texHero;
    raylib::Texture2D texHero_Flip_Horizontal;
    raylib::Vector2 map_pos_in_screen{};
    map_pos_in_screen.x = 0;
    map_pos_in_screen.y = 0;
    texHero= LoadTextureFromImage(hero.m_HeroSet);
    texHero_Flip_Horizontal = LoadTextureFromImage(hero.m_HeroSet_Flip_Horizontal);
    texture1 = LoadTextureFromImage(TheDungeon.m_Environnement.m_Tileset);
    texture2 = LoadTextureFromImage(TheDungeon.map[0]);
    texture3 = LoadTextureFromImage(TheDungeon.map[1]);
    // Custom timming variables
    double previousTime_Hero = raylib::GetTime();
    double previousTime_HeroIdle = raylib::GetTime();
    double previousTime_HeroWalk = raylib::GetTime();
    double currentTime = 0.0;           // Current time measure


    while (!raylib::WindowShouldClose())    // Detect window close button or ESC key
    {
        currentTime = raylib::GetTime();
        if ((currentTime - previousTime_Hero) > 10)
        {
           // hero.m_ActionCourante = 0;
        }
        //----------------------------------------------------------------------------------
        // Draw
        //----------------------------------------------------------------------------------
        raylib::BeginDrawing();

        raylib::ClearBackground(raylib::BLACK);
        if (raylib::IsKeyDown(raylib::KEY_A)) affiche_grille=false;
        if (raylib::IsKeyDown(raylib::KEY_Z)) affiche_grille=true;
        if (raylib::IsKeyDown(raylib::KEY_T)) affiche_tileset = true;
        if (raylib::IsKeyDown(raylib::KEY_G)) affiche_tileset = false;

        if (raylib::IsKeyDown(raylib::KEY_UP))
        {
            hero.m_HeroDir = 1;
            hero.m_HeroActionCourante = 1;
            map_pos_in_screen.y = map_pos_in_screen.y + hero.m_SpeedWalk;
            previousTime_Hero = currentTime;

        }
        if (raylib::IsKeyDown(raylib::KEY_DOWN))
        {
            hero.m_HeroDir = 2;
            hero.m_HeroActionCourante = 1;
            map_pos_in_screen.y = map_pos_in_screen.y - hero.m_SpeedWalk;
            previousTime_Hero = currentTime;
        }
        if (raylib::IsKeyDown(raylib::KEY_LEFT))
        {
            hero.m_HeroDir = 3;
            hero.m_HeroActionCourante = 1;
            map_pos_in_screen.x = map_pos_in_screen.x + hero.m_SpeedWalk;
            previousTime_Hero = currentTime;
        }
        if (raylib::IsKeyDown(raylib::KEY_RIGHT))
        {
            hero.m_HeroDir = 4;
            hero.m_HeroActionCourante = 1;
            map_pos_in_screen.x = map_pos_in_screen.x - hero.m_SpeedWalk;
            previousTime_Hero = currentTime;
        }

        if (raylib::IsKeyDown(raylib::KEY_SPACE))
        {
            hero.m_HeroActionCourante = 2;
        }

        if (affiche_tileset == true)
        {
            raylib::DrawTexture(texture1, 0, 0, raylib::WHITE);
        }
        else
        {
            raylib::DrawTexture(texture2, map_pos_in_screen.x, map_pos_in_screen.y, raylib::WHITE);
            
            switch (hero.m_HeroDir)
            {
                case 0:
                    if ((currentTime - previousTime_HeroIdle) > hero.m_IdleTime)
                    {
                        hero.Idle();
                        previousTime_HeroIdle = currentTime;
                    }
                    raylib::DrawTextureRec(texHero, hero.m_RecHero, hero.m_HeroPos, raylib::WHITE);
                    break;
                case 1: // haut
                case 2: // Bas
                case 3: // Gauche
                    if ((currentTime - previousTime_HeroWalk) > hero.m_Time)
                    {
                        if (hero.m_HeroActionCourante == 2)
                        {
                            hero.m_HeroActionCourante=hero.Attack(hero.m_HeroDir);
                            
                        }
                        if (hero.m_HeroActionCourante == 1)
                        {
                            hero.Walk(hero.m_HeroDir);
                            hero.m_HeroActionCourante = 0;
                        }
                        previousTime_HeroWalk = currentTime;

                    }
                    raylib::DrawTextureRec( texHero_Flip_Horizontal, hero.m_RecHero, hero.m_HeroPos, raylib::WHITE);
                    break;
                case 4: //Droite
                    if ((currentTime - previousTime_HeroWalk) > hero.m_Time)
                    {
                        if (hero.m_HeroActionCourante == 2)
                        {
                            hero.m_HeroActionCourante=hero.Attack(hero.m_HeroDir);
                        }
                        if (hero.m_HeroActionCourante == 1)
                        {
                            hero.Walk(hero.m_HeroDir);
                            hero.m_HeroActionCourante = 0;
                        }
                        previousTime_HeroWalk = currentTime;

                    }

                    raylib::DrawTextureRec(texHero, hero.m_RecHero, hero.m_HeroPos, raylib::WHITE);
                    break;
            }
        
                     
            raylib::DrawTexture(texture3, map_pos_in_screen.x, map_pos_in_screen.y, raylib::WHITE);
        }
       
       if (affiche_tileset == true)
       {
           for (int x = 0; x < TheDungeon.m_Environnement.m_sizeTileSet_x; x++)
           {
               for (int y = 0; y < TheDungeon.m_Environnement.m_sizeTileSet_y; y++)
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
