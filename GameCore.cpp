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
    monstre.Init();
    hero.m_HeroPos.x = ((int((SCREENWIDTH  / TheDungeon.m_Environnement.m_TileSize))/2))* TheDungeon.m_Environnement.m_TileSize;
    hero.m_HeroPos.y = ((int((SCREENHEIGHT / TheDungeon.m_Environnement.m_TileSize))/2))* TheDungeon.m_Environnement.m_TileSize;


}


void GameCore::endGameCore()
{
    raylib::CloseWindow();          // Close window and OpenGL context
}

void GameCore::loopGameCore()
{
    // Main game loop
    bool affiche_tileset = false;
    bool affiche_Collision = false;
    bool affiche_Collision_Box = false;
    raylib::Texture2D texTileSet;
    raylib::Texture2D texMap0;
    raylib::Texture2D texMap1;
    raylib::Texture2D texMap3;
    raylib::Texture2D texHero;
    raylib::Texture2D texHero_Flip_Horizontal;
    raylib::Texture2D texMonstre;
    raylib::Texture2D texMonstre_Flip_Horizontal;
    raylib::Texture2D texPrecipiceMap;
    raylib::Vector2 map_pos_in_screen{};
    map_pos_in_screen.x = ((int((SCREENWIDTH / TheDungeon.m_Environnement.m_TileSize)) / 2) +1) * TheDungeon.m_Environnement.m_TileSize;
    map_pos_in_screen.y = ((int((SCREENHEIGHT / TheDungeon.m_Environnement.m_TileSize)) / 2) +1) * TheDungeon.m_Environnement.m_TileSize;
    map_pos_in_screen.x += -(TheDungeon.Entree.x) * TheDungeon.m_Environnement.m_TileSize;
    map_pos_in_screen.y += -(TheDungeon.Entree.y) * TheDungeon.m_Environnement.m_TileSize;
    texHero= LoadTextureFromImage(hero.m_HeroSet);
    texHero_Flip_Horizontal = LoadTextureFromImage(hero.m_HeroSet_Flip_Horizontal);

    texMonstre = LoadTextureFromImage(monstre.m_Set);
    texMonstre_Flip_Horizontal = LoadTextureFromImage(monstre.m_Set_Flip_Horizontal);

    texTileSet = LoadTextureFromImage(TheDungeon.m_Environnement.m_Tileset);
    texMap0 = LoadTextureFromImage(TheDungeon.map[0]);
    texMap1 = LoadTextureFromImage(TheDungeon.map[1]);
    //texMap2 = LoadTextureFromImage(TheDungeon.map[2]);
    texMap3 = LoadTextureFromImage(TheDungeon.map[3]);
    texPrecipiceMap = LoadTextureFromImage(TheDungeon.PrecipiceMap);
    // Custom timming variables
    double previousTime_Hero = raylib::GetTime();
    double previousTime_HeroIdle = raylib::GetTime();
    double previousTime_HeroWalk = raylib::GetTime();
    double currentTime = 0.0;           // Current time measure
    Block_Interact Interactbox;
    raylib::Rectangle heroBB{};
    raylib::Vector2 TileSizeXY{};
    TileSizeXY.x = (float)TheDungeon.m_Environnement.m_TileSize;
    TileSizeXY.y = (float)TheDungeon.m_Environnement.m_TileSize;
    raylib::Vector2 TilePosXY;
    TilePosXY.x = 0;
    TilePosXY.y = 0;
    raylib::Rectangle rectTile{};
    rectTile.height = TileSizeXY.x;
    rectTile.width = TileSizeXY.y;
    bool GameOver = false;
    double Time_mvt_Etiquette_Sortie = 0;
    int Index_mvt_Etiquette_Sortie = 0;
    int mvt_Etiquette_Sortie[] = {-40,-39,-39,-38,-37,-37,-37,-38,-39,-39,-40,-40};
    while (!raylib::WindowShouldClose())    // Detect window close button or ESC key
    {

        //----------------------------------------------------------------------------------
        // GEstion des Inputs
        //----------------------------------------------------------------------------------
        if (raylib::IsKeyDown(raylib::KEY_U)) affiche_Collision_Box = false;
        if (raylib::IsKeyDown(raylib::KEY_J)) affiche_Collision_Box = true;
        if (raylib::IsKeyDown(raylib::KEY_O)) affiche_tileset = true;
        if (raylib::IsKeyDown(raylib::KEY_L)) affiche_tileset = false;
        if (raylib::IsKeyDown(raylib::KEY_I)) affiche_Collision = true;
        if (raylib::IsKeyDown(raylib::KEY_K)) affiche_Collision = false;

        
        if (GameOver == false)
        {
            currentTime = raylib::GetTime();
            if ((currentTime - previousTime_Hero) > 5)
            {
                hero.m_HeroActionCourante = 0;
                hero.m_HeroDir = 0;
            }
            if (raylib::IsKeyDown(raylib::KEY_SPACE))
            {
                hero.m_HeroActionCourante = 2;
                previousTime_Hero = currentTime;

            }
            // Attack du Hero
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
            // Mouvement du Hero
            if ((hero.m_HeroActionCourante == 0) || (hero.m_HeroActionCourante == 1))
            {
                if (raylib::IsKeyDown(raylib::KEY_E))
                {
                    hero.m_HeroActionCourante = 1;
                    if (hero.m_HeroDir == 1)
                    {
                        heroBB.x = hero.m_HeroPos.x - map_pos_in_screen.x + (hero.m_HeroSize / 2) - (hero.m_CollBoxHero.x/2);
                        heroBB.y = hero.m_HeroPos.y - (map_pos_in_screen.y + hero.m_SpeedWalk) + (hero.m_HeroSize / 2);
                        heroBB.width = hero.m_CollBoxHero.x;
                        heroBB.height = hero.m_CollBoxHero.y;
                    }
                    if (hero.m_HeroDir == 2)
                    {
                        heroBB.x = hero.m_HeroPos.x - map_pos_in_screen.x + (hero.m_HeroSize / 2) - (hero.m_CollBoxHero.x / 2);
                        heroBB.y = hero.m_HeroPos.y - (map_pos_in_screen.y - hero.m_SpeedWalk) + (hero.m_HeroSize / 2);
                        heroBB.width = hero.m_CollBoxHero.x;
                        heroBB.height = hero.m_CollBoxHero.y;
                    }
                    if (hero.m_HeroDir == 3)
                    {
                        heroBB.x = hero.m_HeroPos.x - (map_pos_in_screen.x - hero.m_SpeedWalk) + (hero.m_HeroSize / 2) - (hero.m_CollBoxHero.x / 2);
                        heroBB.y = hero.m_HeroPos.y - (map_pos_in_screen.y) + (hero.m_HeroSize / 2);
                        heroBB.width = hero.m_CollBoxHero.x;
                        heroBB.height = hero.m_CollBoxHero.y;
                    }
                    if (hero.m_HeroDir == 4)
                    {
                        heroBB.x = hero.m_HeroPos.x - (map_pos_in_screen.x + hero.m_SpeedWalk) + (hero.m_HeroSize / 2) - (hero.m_CollBoxHero.x / 2);
                        heroBB.y = hero.m_HeroPos.y - (map_pos_in_screen.y) + (hero.m_HeroSize / 2);
                        heroBB.width = hero.m_CollBoxHero.x;
                        heroBB.height = hero.m_CollBoxHero.y;
                    }


                    if (TheDungeon.isCollisionMap(heroBB, Interactbox) == true)
                    {
                        if ((Interactbox.Type == 1) || (Interactbox.Type == 2) || (Interactbox.Type == 11) || (Interactbox.Type == 12))// porte sans verrou
                        {
                            auto it = std::find(TheDungeon.CollisionMap.begin(), TheDungeon.CollisionMap.end(),
                                Interactbox);

                            if (it != TheDungeon.CollisionMap.end()) {
                                TheDungeon.CollisionMap.erase(it);
                            }

                        }
                        if ((Interactbox.Type == 4) || (Interactbox.Type == 5) || (Interactbox.Type == 14) || (Interactbox.Type == 15))// porte avec verrou
                        {

                        }
                        if ((Interactbox.Type == 6) && (Interactbox.Etat==0)) // Tresors à ouvrir
                        {
                            Block_Interact MajBlock;
                            auto it = std::find(TheDungeon.CollisionMap.begin(), TheDungeon.CollisionMap.end(),
                                Interactbox);

                            if (it != TheDungeon.CollisionMap.end()) {
                                TheDungeon.CollisionMap.erase(it);
                                MajBlock = Interactbox;
                                MajBlock.Etat = 1;
                                
                                TheDungeon.CollisionMap.push_back(MajBlock);
                            }
                        }
                    }
                    previousTime_Hero = currentTime;
                }
                if (raylib::IsKeyDown(raylib::KEY_UP))
                {
                    hero.m_HeroDir = 1;
                    hero.m_HeroActionCourante = 1;

                    heroBB.x = hero.m_HeroPos.x - map_pos_in_screen.x + (hero.m_HeroSize / 2) - (hero.m_CollBoxHero.x / 2);
                    heroBB.y = hero.m_HeroPos.y - (map_pos_in_screen.y + hero.m_SpeedWalk) + (hero.m_HeroSize / 2);
                    heroBB.width = hero.m_CollBoxHero.x;
                    heroBB.height = hero.m_CollBoxHero.y;

                    if (TheDungeon.isCollisionMap(heroBB, Interactbox) == false)
                    {
                        map_pos_in_screen.y = map_pos_in_screen.y + hero.m_SpeedWalk;
                    }
                    raylib::Color pixel = TheDungeon.PrecipiceMapColor[(int)(((hero.m_HeroPos.y - (map_pos_in_screen.y) + (hero.m_HeroSize / 2) + 22) * TheDungeon.sizeMapPixels_x) + (hero.m_HeroPos.x - map_pos_in_screen.x + (hero.m_HeroSize / 2)))];
                    if ((pixel.r == 255) && (pixel.g == 255) && (pixel.b == 255))
                    {
                        hero.m_HeroActionCourante = 3;
                    }
                    previousTime_Hero = currentTime;

                }
                if (raylib::IsKeyDown(raylib::KEY_DOWN))
                {
                    hero.m_HeroDir = 2;
                    hero.m_HeroActionCourante = 1;
                    heroBB.x = hero.m_HeroPos.x - map_pos_in_screen.x + (hero.m_HeroSize / 2) - (hero.m_CollBoxHero.x / 2);
                    heroBB.y = hero.m_HeroPos.y - (map_pos_in_screen.y - hero.m_SpeedWalk) + (hero.m_HeroSize / 2);
                    heroBB.width = hero.m_CollBoxHero.x;
                    heroBB.height = hero.m_CollBoxHero.y;

                    if (TheDungeon.isCollisionMap(heroBB, Interactbox) == false)
                    {
                        map_pos_in_screen.y = map_pos_in_screen.y - hero.m_SpeedWalk;
                    }
                    raylib::Color pixel = TheDungeon.PrecipiceMapColor[(int)(((hero.m_HeroPos.y - (map_pos_in_screen.y) + (hero.m_HeroSize / 2) + 22) * TheDungeon.sizeMapPixels_x) + (hero.m_HeroPos.x - map_pos_in_screen.x + (hero.m_HeroSize / 2)))];
                    if ((pixel.r == 255) && (pixel.g == 255) && (pixel.b == 255))
                    {
                        hero.m_HeroActionCourante = 3;
                    }
                    previousTime_Hero = currentTime;
                }
                if (raylib::IsKeyDown(raylib::KEY_LEFT))
                {
                    hero.m_HeroDir = 4;
                    hero.m_HeroActionCourante = 1;
                    heroBB.x = hero.m_HeroPos.x - (map_pos_in_screen.x + hero.m_SpeedWalk) + (hero.m_HeroSize / 2) - (hero.m_CollBoxHero.x / 2);
                    heroBB.y = hero.m_HeroPos.y - (map_pos_in_screen.y) + (hero.m_HeroSize / 2);
                    heroBB.width = hero.m_CollBoxHero.x;
                    heroBB.height = hero.m_CollBoxHero.y;

                    if (TheDungeon.isCollisionMap(heroBB, Interactbox) == false)
                    {
                        map_pos_in_screen.x = map_pos_in_screen.x + hero.m_SpeedWalk;
                    }
                    raylib::Color pixel = TheDungeon.PrecipiceMapColor[(int)(((hero.m_HeroPos.y - (map_pos_in_screen.y) + (hero.m_HeroSize / 2) + 22) * TheDungeon.sizeMapPixels_x) + (hero.m_HeroPos.x - map_pos_in_screen.x + (hero.m_HeroSize / 2)))];
                    if ((pixel.r == 255) && (pixel.g == 255) && (pixel.b == 255))
                    {
                        hero.m_HeroActionCourante = 3;
                    }
                    previousTime_Hero = currentTime;
                }
                if (raylib::IsKeyDown(raylib::KEY_RIGHT))
                {
                    hero.m_HeroDir = 3;
                    hero.m_HeroActionCourante = 1;
                    heroBB.x = hero.m_HeroPos.x - (map_pos_in_screen.x - hero.m_SpeedWalk) + (hero.m_HeroSize / 2) - (hero.m_CollBoxHero.x / 2);
                    heroBB.y = hero.m_HeroPos.y - (map_pos_in_screen.y) + (hero.m_HeroSize / 2);
                    heroBB.width = hero.m_CollBoxHero.x;
                    heroBB.height = hero.m_CollBoxHero.y;

                    if (TheDungeon.isCollisionMap(heroBB, Interactbox) == false)
                    {
                        map_pos_in_screen.x = map_pos_in_screen.x - hero.m_SpeedWalk;
                    }
                    previousTime_Hero = currentTime;
                    raylib::Color pixel = TheDungeon.PrecipiceMapColor[(int)(((hero.m_HeroPos.y - (map_pos_in_screen.y) + (hero.m_HeroSize / 2) + 22) * TheDungeon.sizeMapPixels_x) + (hero.m_HeroPos.x - map_pos_in_screen.x + (hero.m_HeroSize / 2)))];
                    if ((pixel.r == 255) && (pixel.g == 255) && (pixel.b == 255))
                    {
                        hero.m_HeroActionCourante = 3;
                    }

                }

            }
            // Mouvement des monstres
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
        else if (affiche_Collision == true)
        {
            raylib::DrawTexture(texPrecipiceMap, map_pos_in_screen.x, map_pos_in_screen.y, raylib::WHITE);
        }
        else
        {
            // Draw sol + mur
            raylib::DrawTexture(texMap0, map_pos_in_screen.x, map_pos_in_screen.y, raylib::WHITE);
            // Draw detail sol
            raylib::DrawTexture(texMap1, map_pos_in_screen.x, map_pos_in_screen.y, raylib::WHITE);
            // Draw porte + grille
            for (Block_Interact box : TheDungeon.CollisionMap)
            {
                switch (box.Type)
                {
                case 1: // Porte Horizontal
                    // 1 x block
                    TilePosXY = TheDungeon.m_Environnement.getTile(237);
                    rectTile.x = TilePosXY.x;
                    rectTile.y = TilePosXY.y;
                    DrawTextureRec(texTileSet, rectTile, raylib::Vector2{ (float)(map_pos_in_screen.x + (box.x * (float)TheDungeon.m_Environnement.m_TileSize)), (float)(map_pos_in_screen.y + (box.y * (float)TheDungeon.m_Environnement.m_TileSize)) }, raylib::WHITE);

                    break;
                case 2: // Grille Horizontal
                    // 1 x block
                    TilePosXY = TheDungeon.m_Environnement.getTile(214);
                    rectTile.x = TilePosXY.x;
                    rectTile.y = TilePosXY.y;
                    DrawTextureRec(texTileSet, rectTile, raylib::Vector2{ (float)(map_pos_in_screen.x + (box.x * (float)TheDungeon.m_Environnement.m_TileSize)), (float)(map_pos_in_screen.y + (box.y * (float)TheDungeon.m_Environnement.m_TileSize)) }, raylib::WHITE);
                    break;
                case 3: // Arch Horizontal
                    // 6 x block
                    TilePosXY = TheDungeon.m_Environnement.getTile(240);
                    rectTile.x = TilePosXY.x;
                    rectTile.y = TilePosXY.y;

                    DrawTextureRec(texTileSet, rectTile, raylib::Vector2{ (float)(map_pos_in_screen.x + ((box.x - 1) * (float)TheDungeon.m_Environnement.m_TileSize)), (float)(map_pos_in_screen.y + ((box.y - 1) * (float)TheDungeon.m_Environnement.m_TileSize)) }, raylib::WHITE);

                    TilePosXY = TheDungeon.m_Environnement.getTile(260);
                    rectTile.x = TilePosXY.x;
                    rectTile.y = TilePosXY.y;

                    DrawTextureRec(texTileSet, rectTile, raylib::Vector2{ (float)(map_pos_in_screen.x + ((box.x - 1) * (float)TheDungeon.m_Environnement.m_TileSize)), (float)(map_pos_in_screen.y + ((box.y) * (float)TheDungeon.m_Environnement.m_TileSize)) }, raylib::WHITE);
                    TilePosXY = TheDungeon.m_Environnement.getTile(241);
                    rectTile.x = TilePosXY.x;
                    rectTile.y = TilePosXY.y;

                    DrawTextureRec(texTileSet, rectTile, raylib::Vector2{ (float)(map_pos_in_screen.x + ((box.x) * (float)TheDungeon.m_Environnement.m_TileSize)), (float)(map_pos_in_screen.y + ((box.y - 1) * (float)TheDungeon.m_Environnement.m_TileSize)) }, raylib::WHITE);
                    TilePosXY = TheDungeon.m_Environnement.getTile(261);
                    rectTile.x = TilePosXY.x;
                    rectTile.y = TilePosXY.y;

                    DrawTextureRec(texTileSet, rectTile, raylib::Vector2{ (float)(map_pos_in_screen.x + ((box.x) * (float)TheDungeon.m_Environnement.m_TileSize)), (float)(map_pos_in_screen.y + ((box.y) * (float)TheDungeon.m_Environnement.m_TileSize)) }, raylib::WHITE);                        TilePosXY = TheDungeon.m_Environnement.getTile(242);
                    rectTile.x = TilePosXY.x;
                    rectTile.y = TilePosXY.y;

                    DrawTextureRec(texTileSet, rectTile, raylib::Vector2{ (float)(map_pos_in_screen.x + ((box.x + 1) * (float)TheDungeon.m_Environnement.m_TileSize)), (float)(map_pos_in_screen.y + ((box.y - 1) * (float)TheDungeon.m_Environnement.m_TileSize)) }, raylib::WHITE);
                    TilePosXY = TheDungeon.m_Environnement.getTile(262);
                    rectTile.x = TilePosXY.x;
                    rectTile.y = TilePosXY.y;

                    DrawTextureRec(texTileSet, rectTile, raylib::Vector2{ (float)(map_pos_in_screen.x + ((box.x + 1) * (float)TheDungeon.m_Environnement.m_TileSize)), (float)(map_pos_in_screen.y + ((box.y) * (float)TheDungeon.m_Environnement.m_TileSize)) }, raylib::WHITE);
                    break;
                case 4:
                case 5:// Porte Horizontal Lock
                    // 1 x block
                    TilePosXY = TheDungeon.m_Environnement.getTile(234);
                    rectTile.x = TilePosXY.x;
                    rectTile.y = TilePosXY.y;
                    DrawTextureRec(texTileSet, rectTile, raylib::Vector2{ (float)(map_pos_in_screen.x + (box.x * (float)TheDungeon.m_Environnement.m_TileSize)), (float)(map_pos_in_screen.y + (box.y * (float)TheDungeon.m_Environnement.m_TileSize)) }, raylib::WHITE);

                    break;
               /* case 5: // Porte Horizontal Blocké
                    // 1 x block
                    TilePosXY = TheDungeon.m_Environnement.getTile(288);
                    rectTile.x = TilePosXY.x;
                    rectTile.y = TilePosXY.y;
                    DrawTextureRec(texTileSet, rectTile, raylib::Vector2{ (float)(map_pos_in_screen.x + (box.x * (float)TheDungeon.m_Environnement.m_TileSize)), (float)(map_pos_in_screen.y + (box.y * (float)TheDungeon.m_Environnement.m_TileSize)) }, raylib::WHITE);

                    break;*/
                case 6: // tresors
                    if (box.Etat == 0)
                    {
                        TilePosXY = TheDungeon.m_Environnement.getTile(334);
                    }
                    else
                    {
                        TilePosXY = TheDungeon.m_Environnement.getTile(335);
                    }
                    rectTile.x = TilePosXY.x;
                    rectTile.y = TilePosXY.y;
                    DrawTextureRec(texTileSet, rectTile, raylib::Vector2{ (float)(map_pos_in_screen.x + (box.x * (float)TheDungeon.m_Environnement.m_TileSize)), (float)(map_pos_in_screen.y + (box.y * (float)TheDungeon.m_Environnement.m_TileSize)) }, raylib::WHITE);

                    break;
                case 11: // Porte  Verttical
                    // 2 x blocks
                    TilePosXY = TheDungeon.m_Environnement.getTile(218);
                    rectTile.x = TilePosXY.x;
                    rectTile.y = TilePosXY.y;
                    DrawTextureRec(texTileSet, rectTile, raylib::Vector2{ (float)(map_pos_in_screen.x + (box.x * (float)TheDungeon.m_Environnement.m_TileSize)), (float)(map_pos_in_screen.y + ((box.y - 1) * (float)TheDungeon.m_Environnement.m_TileSize)) }, raylib::WHITE);


                    TilePosXY = TheDungeon.m_Environnement.getTile(238);
                    rectTile.x = TilePosXY.x;
                    rectTile.y = TilePosXY.y;

                    DrawTextureRec(texTileSet, rectTile, raylib::Vector2{ (float)(map_pos_in_screen.x + (box.x * (float)TheDungeon.m_Environnement.m_TileSize)), (float)(map_pos_in_screen.y + (box.y * (float)TheDungeon.m_Environnement.m_TileSize)) }, raylib::WHITE);
                    break;
                case 12: // Grille  Verttical
                    // 2 x blocks
                    TilePosXY = TheDungeon.m_Environnement.getTile(216);
                    rectTile.x = TilePosXY.x;
                    rectTile.y = TilePosXY.y;

                    DrawTextureRec(texTileSet, rectTile, raylib::Vector2{ (float)(map_pos_in_screen.x + (box.x * (float)TheDungeon.m_Environnement.m_TileSize)), (float)(map_pos_in_screen.y + ((box.y - 1) * (float)TheDungeon.m_Environnement.m_TileSize)) }, raylib::WHITE);
                    TilePosXY = TheDungeon.m_Environnement.getTile(236);
                    rectTile.x = TilePosXY.x;
                    rectTile.y = TilePosXY.y;
                    DrawTextureRec(texTileSet, rectTile, raylib::Vector2{ (float)(map_pos_in_screen.x + (box.x * (float)TheDungeon.m_Environnement.m_TileSize)), (float)(map_pos_in_screen.y + (box.y * (float)TheDungeon.m_Environnement.m_TileSize)) }, raylib::WHITE);
                    break;
                case 14: // Porte  Verttical Lock
                case 15:
                    // 2 x blocks
                    TilePosXY = TheDungeon.m_Environnement.getTile(215);
                    rectTile.x = TilePosXY.x;
                    rectTile.y = TilePosXY.y;

                    DrawTextureRec(texTileSet, rectTile, raylib::Vector2{ (float)(map_pos_in_screen.x + (box.x * (float)TheDungeon.m_Environnement.m_TileSize)), (float)(map_pos_in_screen.y + ((box.y - 1) * (float)TheDungeon.m_Environnement.m_TileSize)) }, raylib::WHITE);

                    TilePosXY = TheDungeon.m_Environnement.getTile(235);
                    rectTile.x = TilePosXY.x;
                    rectTile.y = TilePosXY.y;

                    DrawTextureRec(texTileSet, rectTile, raylib::Vector2{ (float)(map_pos_in_screen.x + (box.x * (float)TheDungeon.m_Environnement.m_TileSize)), (float)(map_pos_in_screen.y + (box.y * (float)TheDungeon.m_Environnement.m_TileSize)) }, raylib::WHITE);

                    break;
                /*case 15: // Porte Verttical Blocké
                    // 1 x block
                    TilePosXY = TheDungeon.m_Environnement.getTile(288);
                    rectTile.x = TilePosXY.x;
                    rectTile.y = TilePosXY.y;

                    DrawTextureRec(texTileSet, rectTile, raylib::Vector2{ (float)(map_pos_in_screen.x + (box.x * (float)TheDungeon.m_Environnement.m_TileSize)), (float)(map_pos_in_screen.y + (box.y * (float)TheDungeon.m_Environnement.m_TileSize)) }, raylib::WHITE);
                    
                    break;*/
                }
            }
            if (affiche_Collision_Box == true)
            {
                raylib::DrawTexture(texPrecipiceMap, map_pos_in_screen.x, map_pos_in_screen.y, raylib::WHITE);

                heroBB.x = hero.m_HeroPos.x + (hero.m_HeroSize / 2) - (hero.m_CollBoxHero.x / 2);
                heroBB.y = hero.m_HeroPos.y + (hero.m_HeroSize / 2);
                raylib::DrawRectangleLines(heroBB.x, heroBB.y, hero.m_CollBoxHero.x, hero.m_CollBoxHero.y, raylib::RED);
            }
            if (GameOver == false)
            {
                raylib::DrawTextureRec(texMonstre, monstre.m_Rec, monstre.m_Pos, raylib::WHITE);
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

                        if (hero.m_HeroActionCourante == 3)
                        {
                            hero.m_HeroActionCourante = hero.Chute(hero.m_HeroDir);
                        }
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
            }
            // Draw des Arch pour deco
            raylib::DrawTexture(texMap3, map_pos_in_screen.x, map_pos_in_screen.y, raylib::WHITE);
            
            //Draw etiquette de sortie
            if ((currentTime - Time_mvt_Etiquette_Sortie) > 0.080)
            {
                Index_mvt_Etiquette_Sortie = (Index_mvt_Etiquette_Sortie + 1) % 12;

                Time_mvt_Etiquette_Sortie = currentTime;
            }
            TilePosXY = TheDungeon.m_Environnement.getTile(199);
            rectTile.x = TilePosXY.x;
            rectTile.y = TilePosXY.y;
            raylib::DrawTextureRec(texTileSet, rectTile, raylib::Vector2{ (float)(map_pos_in_screen.x + (TheDungeon.Sortie.x * (float)TheDungeon.m_Environnement.m_TileSize)), (float)(map_pos_in_screen.y + (TheDungeon.Sortie.y * (float)TheDungeon.m_Environnement.m_TileSize) + mvt_Etiquette_Sortie[Index_mvt_Etiquette_Sortie]) }, raylib::Color{255,255,255,200});



        }

        if (affiche_tileset == true)
        {
            for (int x = 0; x < TheDungeon.m_Environnement.m_sizeTileSet_x; x++)
            {
                for (int y = 0; y < TheDungeon.m_Environnement.m_sizeTileSet_y; y++)
                {
                    raylib::DrawRectangleLines(x * 48, y * 48, 48, 48, raylib::GRAY);
                    
                    raylib::DrawText(raylib::TextFormat("%d", x + y * 20), (x * 48) + 5, (y * 48) + 5, 10, raylib::WHITE);
                }
            }
        }

        if (hero.m_HeroActionCourante == 4)
        {
            raylib::DrawText(raylib::TextFormat("GAME OVER"), SCREENWIDTH / 2, SCREENHEIGHT / 2, 40, raylib::WHITE);
            GameOver = true;
        }


        raylib::EndDrawing();
  
    }

}
void GameCore::MortDuHero(int type)
{
    // Type = 0 ==> tombe
    
}
