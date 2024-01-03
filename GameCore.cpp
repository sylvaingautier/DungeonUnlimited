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
    bool affiche_mapCollision = false;
    raylib::Texture2D texTileSet;
    raylib::Texture2D texMap0;
    raylib::Texture2D texMap1;
    raylib::Texture2D texMap2;
    raylib::Texture2D texMap3;
    raylib::Texture2D texHero;
    raylib::Texture2D texHero_Flip_Horizontal;
    raylib::Texture2D texmapCollision;
    raylib::Vector2 map_pos_in_screen{};
    map_pos_in_screen.x = 0;
    map_pos_in_screen.y = 0;
    texHero= LoadTextureFromImage(hero.m_HeroSet);
    texHero_Flip_Horizontal = LoadTextureFromImage(hero.m_HeroSet_Flip_Horizontal);
    texTileSet = LoadTextureFromImage(TheDungeon.m_Environnement.m_Tileset);
    texMap0 = LoadTextureFromImage(TheDungeon.map[0]);
    texMap1 = LoadTextureFromImage(TheDungeon.map[1]);
    texMap2 = LoadTextureFromImage(TheDungeon.map[2]);
    texMap3 = LoadTextureFromImage(TheDungeon.map[3]);
    // Custom timming variables
    double previousTime_Hero = raylib::GetTime();
    double previousTime_HeroIdle = raylib::GetTime();
    double previousTime_HeroWalk = raylib::GetTime();
    double currentTime = 0.0;           // Current time measure
    Environnements::s_Collision_Block Collbox;
    raylib::Rectangle heroBB{};
    while (!raylib::WindowShouldClose())    // Detect window close button or ESC key
    {
        currentTime = raylib::GetTime();
        if ((currentTime - previousTime_Hero) > 5)
        {
            hero.m_HeroActionCourante = 0;
            hero.m_HeroDir = 0;
        }

        //----------------------------------------------------------------------------------
        // GEstion des Inputs
        //----------------------------------------------------------------------------------
        if (raylib::IsKeyDown(raylib::KEY_U)) affiche_grille=false;
        if (raylib::IsKeyDown(raylib::KEY_J)) affiche_grille=true;
        if (raylib::IsKeyDown(raylib::KEY_O)) affiche_tileset = true;
        if (raylib::IsKeyDown(raylib::KEY_L)) affiche_tileset = false;
        if (raylib::IsKeyDown(raylib::KEY_I)) affiche_mapCollision = true;
        if (raylib::IsKeyDown(raylib::KEY_K)) affiche_mapCollision = false;

        if (raylib::IsKeyDown(raylib::KEY_SPACE))
        {
            hero.m_HeroActionCourante = 2;
            previousTime_Hero = currentTime;

        }
        if (hero.m_HeroActionCourante == 2)
        {
            if (raylib::IsKeyDown(raylib::KEY_UP))
            {
                hero.m_HeroDir = 1;
                previousTime_Hero = currentTime;

            }
            if (raylib::IsKeyDown(raylib::KEY_DOWN))
            {
                hero.m_HeroDir = 2;
                previousTime_Hero = currentTime;
            }
            if (raylib::IsKeyDown(raylib::KEY_LEFT))
            {
                hero.m_HeroDir = 4;
                previousTime_Hero = currentTime;
            }
            if (raylib::IsKeyDown(raylib::KEY_RIGHT))
            {
                hero.m_HeroDir = 3;
                previousTime_Hero = currentTime;
            }
        }
        else
        {

            if (raylib::IsKeyDown(raylib::KEY_UP))
            {
                hero.m_HeroDir = 1;
                hero.m_HeroActionCourante = 1;

                heroBB.x = hero.m_HeroPos.x - map_pos_in_screen.x + (hero.m_HeroSize / 2) - 22;
                heroBB.y = hero.m_HeroPos.y - (map_pos_in_screen.y + hero.m_SpeedWalk) + (hero.m_HeroSize / 2);
                heroBB.width =  44;
                heroBB.height =  22;

                if (TheDungeon.isCollisionMap(heroBB,Collbox) == false)
                {
                    map_pos_in_screen.y = map_pos_in_screen.y + hero.m_SpeedWalk;
                }
                previousTime_Hero = currentTime;

            }
            if (raylib::IsKeyDown(raylib::KEY_DOWN))
            {
                hero.m_HeroDir = 2;
                hero.m_HeroActionCourante = 1;
                heroBB.x = hero.m_HeroPos.x - map_pos_in_screen.x + (hero.m_HeroSize / 2) - 22;
                heroBB.y = hero.m_HeroPos.y - (map_pos_in_screen.y - hero.m_SpeedWalk) + (hero.m_HeroSize / 2);
                heroBB.width =  44;
                heroBB.height =  22;

                if (TheDungeon.isCollisionMap(heroBB, Collbox) == false)
                {
                    map_pos_in_screen.y = map_pos_in_screen.y - hero.m_SpeedWalk;
                }
                previousTime_Hero = currentTime;
            }
            if (raylib::IsKeyDown(raylib::KEY_LEFT))
            {
                hero.m_HeroDir = 4;
                hero.m_HeroActionCourante = 1;
                heroBB.x = hero.m_HeroPos.x - (map_pos_in_screen.x + hero.m_SpeedWalk) + (hero.m_HeroSize / 2) - 22;
                heroBB.y = hero.m_HeroPos.y - (map_pos_in_screen.y) + (hero.m_HeroSize / 2);
                heroBB.width =  44;
                heroBB.height =  22;

                if (TheDungeon.isCollisionMap(heroBB, Collbox) == false)
                {
                    map_pos_in_screen.x = map_pos_in_screen.x + hero.m_SpeedWalk;
                }

                previousTime_Hero = currentTime;
            }
            if (raylib::IsKeyDown(raylib::KEY_RIGHT))
            {
                hero.m_HeroDir = 3;
                hero.m_HeroActionCourante = 1;
                heroBB.x = hero.m_HeroPos.x - (map_pos_in_screen.x - hero.m_SpeedWalk) + (hero.m_HeroSize / 2) - 22;
                heroBB.y = hero.m_HeroPos.y - (map_pos_in_screen.y) + (hero.m_HeroSize / 2);
                heroBB.width =  44;
                heroBB.height =  22;

                if (TheDungeon.isCollisionMap(heroBB, Collbox) == false)
                {
                    {
                        map_pos_in_screen.x = map_pos_in_screen.x - hero.m_SpeedWalk;
                    }
                    previousTime_Hero = currentTime;
                }
            }

        }
        //----------------------------------------------------------------------------------
        // Draw
        //----------------------------------------------------------------------------------
        raylib::BeginDrawing();
        raylib::ClearBackground(raylib::BLACK);
        if (affiche_tileset == true)
        {
            raylib::DrawTexture(texTileSet, 0, 0, raylib::WHITE);
        }
        else if (affiche_mapCollision == true)
        {

        }
        else
        {
            raylib::DrawTexture(texMap0, map_pos_in_screen.x, map_pos_in_screen.y, raylib::WHITE);
            raylib::DrawTexture(texMap1, map_pos_in_screen.x, map_pos_in_screen.y, raylib::WHITE);
            raylib::DrawTexture(texMap2, map_pos_in_screen.x, map_pos_in_screen.y, raylib::WHITE);
            if (hero.m_HeroDir == 0)
            {
                if ((currentTime - previousTime_HeroIdle) > hero.m_TimeWait)
                {
                    hero.Idle();
                    previousTime_HeroIdle = currentTime;
                }
                raylib::DrawTextureRec(texHero, hero.m_RecHero, hero.m_HeroPos, raylib::WHITE);
            }
            else
            {
                if ((currentTime - previousTime_HeroWalk) > hero.m_TimeWait)
                {
                    if (hero.m_HeroActionCourante == 2)
                    {
                        hero.m_HeroActionCourante = hero.Attack(hero.m_HeroDir);
                    }
                    if (hero.m_HeroActionCourante == 1)
                    {
                        hero.Walk(hero.m_HeroDir);
                        hero.m_HeroActionCourante = 0;
                    }
                    previousTime_HeroWalk = currentTime;
                }
                raylib::Vector2 Mvt = hero.m_MicroMvtHero;
                Mvt.x += hero.m_HeroPos.x;
                Mvt.y += hero.m_HeroPos.y;
                if (hero.m_HeroDir == 4)
                {
                    raylib::DrawTextureRec(texHero_Flip_Horizontal, hero.m_RecHero, Mvt, raylib::WHITE); //raylib::Color{ 255,255,255,255});
                }
                else
                {
                    raylib::DrawTextureRec(texHero, hero.m_RecHero, Mvt, raylib::WHITE);
                }
            }
            raylib::DrawTexture(texMap3, map_pos_in_screen.x, map_pos_in_screen.y, raylib::WHITE);
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
