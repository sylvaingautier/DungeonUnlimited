#include "Dungeon_map.h"


Dungeon_map::Dungeon_map()
{
    // Chargement TileSet
    m_Environnement.Init();
    // Chargement des Sprites
    LoadSprites();

    std::ifstream ifs{ R"(Resources/donjon/The Tunnels of Shiva the Destroyer 02.json)" };// The Dark Crypts of the Lich Princess 01.json)" };
    if (!ifs.is_open())
    {
        std::cerr << "Could not open file for reading!\n";
        return;
    }

    IStreamWrapper isw{ ifs };
    d.ParseStream(isw);
    int size_y = d["cells"].Capacity();
    int size_x = d["cells"][0].Capacity();
    sizeMapPixels_x = size_x * 48;
    sizeMapPixels_y = size_y * 48;
    map[0] = raylib::GenImageColor(size_x * 48, size_y * 48, raylib::BLANK);
    map[1] = raylib::GenImageColor(size_x * 48, size_y * 48, raylib::BLANK);
    map[2] = raylib::GenImageColor(size_x * 48, size_y * 48, raylib::BLANK);
    mapCollision = raylib::GenImageColor(size_x * 48, size_y * 48, raylib::BLANK);

    raylib::Vector2 TileSizeXY;
    TileSizeXY.x = (float)m_Environnement.m_TileSize;
    TileSizeXY.y = (float)m_Environnement.m_TileSize;

    raylib::Vector2 TilePosXY;
    TilePosXY.x = 0;
    TilePosXY.y = 0;

    raylib::Rectangle rectTile{};
    rectTile.height = TileSizeXY.x;
    rectTile.width = TileSizeXY.y;

    //Couche N°0 (Couche Fixe)
    for (int x = 0; x < size_x; x++)
    {
        for (int y = 0; y < size_y; y++)
        {
            TilePosXY = m_Environnement.getTile(m_Environnement.m_Block.getTilesetBlock(
                d["cells"][y][x].GetInt64(),
                (y == 0) ? 0 : d["cells"][y - 1][x].GetInt64(),
                (y == (size_y - 1)) ? 0 : d["cells"][y + 1][x].GetInt64(),
                (x == 0) ? 0 : d["cells"][y][x - 1].GetInt64(),
                (x == (size_x - 1)) ? 0 : d["cells"][y][x + 1].GetInt64()));
            
            rectTile.x = TilePosXY.x;
            rectTile.y = TilePosXY.y;

            raylib::ImageDraw(&map[0], m_Environnement.m_Tileset,
                rectTile,
                raylib::Rectangle{ (float)(x* m_Environnement.m_TileSize), (float)(y* m_Environnement.m_TileSize), TileSizeXY.x,TileSizeXY.y },
                raylib::WHITE);
            //CollisionMap
            raylib::BoundingBox Box{};
            Box.min.x = (float)(x * m_Environnement.m_TileSize);
            Box.min.y = (float)(y * m_Environnement.m_TileSize);
            Box.min.z = 0;
            Box.max.x = (float)(x * m_Environnement.m_TileSize) + TileSizeXY.x;
            Box.max.y = (float)(y * m_Environnement.m_TileSize) + TileSizeXY.y;
            Box.max.z = 0;
            CollisionMap.push_back(Box);

            raylib::ImageDrawRectangle(&mapCollision, x * m_Environnement.m_TileSize, y * m_Environnement.m_TileSize, TileSizeXY.x, TileSizeXY.y, m_Environnement.m_Block.getBlockType(d["cells"][y][x].GetInt64()));       // Draw rectangle within an image

        }
    }
    //Couche N°1 (Details Couche Fixe)
    // Detail N°1 : ajout des coins des bordures
    for (int x = 1; x < (size_x-1); x++)
    {
        for (int y = 1; y < (size_y-1); y++)
        {
            std::vector<int> TypeBlock = m_Environnement.m_Block.getTilesetBlockDetail(
                d["cells"][y][x].GetInt64(),
                d["cells"][y - 1][x - 1].GetInt64(),
                d["cells"][y - 1][x + 1].GetInt64(),
                d["cells"][y + 1][x - 1].GetInt64(),
                d["cells"][y + 1][x + 1].GetInt64(),
                d["cells"][y - 1][x].GetInt64(),
                d["cells"][y + 1][x].GetInt64(),
                d["cells"][y][x - 1].GetInt64(),
                d["cells"][y][x + 1].GetInt64());
            for (int block : TypeBlock)
            {
                if (block != 0)
                {
                    TilePosXY = m_Environnement.getTile(block);

                    rectTile.x = TilePosXY.x;
                    rectTile.y = TilePosXY.y;

                    raylib::ImageDraw(&map[1], m_Environnement.m_Tileset,
                        rectTile,
                        raylib::Rectangle{ (float)(x * m_Environnement.m_TileSize), (float)(y * m_Environnement.m_TileSize), TileSizeXY.x,TileSizeXY.y },
                        raylib::WHITE);
                }
            }

        }

    }
    //Couche N°2 (ouverture(Porte/Grille/Arche))
    for (int x = 0; x < size_x; x++)
    {
        for (int y = 0; y < size_y; y++)
        {
            
            int type_ouverture=m_Environnement.m_Block.isDoor(d["cells"][y][x].GetInt64(),
                (y == 0) ? 0 : d["cells"][y - 1][x].GetInt64(),
                (y == (size_y - 1)) ? 0 : d["cells"][y + 1][x].GetInt64(),
                (x == 0) ? 0 : d["cells"][y][x - 1].GetInt64(),
                (x == (size_x - 1)) ? 0 : d["cells"][y][x + 1].GetInt64());
            
            switch (type_ouverture)
            {
                case 1: // Porte Horizontal
                    // 1 x block
                    TilePosXY = m_Environnement.getTile(237);
                    rectTile.x = TilePosXY.x;
                    rectTile.y = TilePosXY.y;

                    raylib::ImageDraw(&map[2], m_Environnement.m_Tileset,
                        rectTile,
                        raylib::Rectangle{ (float)(x * m_Environnement.m_TileSize), (float)(y * m_Environnement.m_TileSize), TileSizeXY.x,TileSizeXY.y },
                        raylib::WHITE);
                    break;
                case 2: // Grille Horizontal
                    // 1 x block
                    TilePosXY = m_Environnement.getTile(214);
                    rectTile.x = TilePosXY.x;
                    rectTile.y = TilePosXY.y;

                    raylib::ImageDraw(&map[2], m_Environnement.m_Tileset,
                        rectTile,
                        raylib::Rectangle{ (float)(x * m_Environnement.m_TileSize), (float)(y * m_Environnement.m_TileSize), TileSizeXY.x,TileSizeXY.y },
                        raylib::WHITE);
                    break;
                case 3: // Arch Horizontal
                    // 6 x block
                    TilePosXY = m_Environnement.getTile(240);
                    rectTile.x = TilePosXY.x;
                    rectTile.y = TilePosXY.y;

                    raylib::ImageDraw(&map[2], m_Environnement.m_Tileset,
                        rectTile,
                        raylib::Rectangle{ (float)((x-1) * m_Environnement.m_TileSize), (float)((y - 1) * m_Environnement.m_TileSize), TileSizeXY.x,TileSizeXY.y },
                        raylib::WHITE);
                    TilePosXY = m_Environnement.getTile(260);
                    rectTile.x = TilePosXY.x;
                    rectTile.y = TilePosXY.y;

                    raylib::ImageDraw(&map[2], m_Environnement.m_Tileset,
                        rectTile,
                        raylib::Rectangle{ (float)((x-1) * m_Environnement.m_TileSize), (float)(y * m_Environnement.m_TileSize), TileSizeXY.x,TileSizeXY.y },
                        raylib::WHITE);
                    
                    TilePosXY = m_Environnement.getTile(241);
                    rectTile.x = TilePosXY.x;
                    rectTile.y = TilePosXY.y;

                    raylib::ImageDraw(&map[2], m_Environnement.m_Tileset,
                        rectTile,
                        raylib::Rectangle{ (float)(x * m_Environnement.m_TileSize), (float)((y-1) * m_Environnement.m_TileSize), TileSizeXY.x,TileSizeXY.y },
                        raylib::WHITE);
                    TilePosXY = m_Environnement.getTile(261);
                    rectTile.x = TilePosXY.x;
                    rectTile.y = TilePosXY.y;

                    raylib::ImageDraw(&map[2], m_Environnement.m_Tileset,
                        rectTile,
                        raylib::Rectangle{ (float)(x * m_Environnement.m_TileSize), (float)(y * m_Environnement.m_TileSize), TileSizeXY.x,TileSizeXY.y },
                        raylib::WHITE);
                    TilePosXY = m_Environnement.getTile(242);
                    rectTile.x = TilePosXY.x;
                    rectTile.y = TilePosXY.y;

                    raylib::ImageDraw(&map[2], m_Environnement.m_Tileset,
                        rectTile,
                        raylib::Rectangle{ (float)((x + 1) * m_Environnement.m_TileSize), (float)((y - 1) * m_Environnement.m_TileSize), TileSizeXY.x,TileSizeXY.y },
                        raylib::WHITE);
                    TilePosXY = m_Environnement.getTile(262);
                    rectTile.x = TilePosXY.x;
                    rectTile.y = TilePosXY.y;

                    raylib::ImageDraw(&map[2], m_Environnement.m_Tileset,
                        rectTile,
                        raylib::Rectangle{ (float)((x + 1) * m_Environnement.m_TileSize), (float)(y * m_Environnement.m_TileSize), TileSizeXY.x,TileSizeXY.y },
                        raylib::WHITE);
                    break;
                case 4: // Porte Horizontal Lock
                    // 1 x block
                    TilePosXY = m_Environnement.getTile(234);
                    rectTile.x = TilePosXY.x;
                    rectTile.y = TilePosXY.y;

                    raylib::ImageDraw(&map[2], m_Environnement.m_Tileset,
                        rectTile,
                        raylib::Rectangle{ (float)(x * m_Environnement.m_TileSize), (float)(y * m_Environnement.m_TileSize), TileSizeXY.x,TileSizeXY.y },
                        raylib::WHITE);
                    break;
                case 5: // Porte Horizontal Blocké
                    // 1 x block
                    TilePosXY = m_Environnement.getTile(288);
                    rectTile.x = TilePosXY.x;
                    rectTile.y = TilePosXY.y;

                    raylib::ImageDraw(&map[2], m_Environnement.m_Tileset,
                        rectTile,
                        raylib::Rectangle{ (float)(x * m_Environnement.m_TileSize), (float)(y * m_Environnement.m_TileSize), TileSizeXY.x,TileSizeXY.y },
                        raylib::WHITE);
                    break;
                case 11: // Porte  Verttical
                    // 2 x blocks
                    TilePosXY = m_Environnement.getTile(218);
                    rectTile.x = TilePosXY.x;
                    rectTile.y = TilePosXY.y;

                    raylib::ImageDraw(&map[2], m_Environnement.m_Tileset,
                        rectTile,
                        raylib::Rectangle{ (float)((x) * m_Environnement.m_TileSize), (float)((y-1) * m_Environnement.m_TileSize), TileSizeXY.x,TileSizeXY.y },
                        raylib::WHITE);
                    TilePosXY = m_Environnement.getTile(238);
                    rectTile.x = TilePosXY.x;
                    rectTile.y = TilePosXY.y;

                    raylib::ImageDraw(&map[2], m_Environnement.m_Tileset,
                        rectTile,
                        raylib::Rectangle{ (float)(x * m_Environnement.m_TileSize), (float)(y * m_Environnement.m_TileSize), TileSizeXY.x,TileSizeXY.y },
                        raylib::WHITE);
                    break;
                case 12: // Grille  Verttical
                    // 2 x blocks
                    TilePosXY = m_Environnement.getTile(216);
                    rectTile.x = TilePosXY.x;
                    rectTile.y = TilePosXY.y;

                    raylib::ImageDraw(&map[2], m_Environnement.m_Tileset,
                        rectTile,
                        raylib::Rectangle{ (float)((x)*m_Environnement.m_TileSize), (float)((y - 1) * m_Environnement.m_TileSize), TileSizeXY.x,TileSizeXY.y },
                        raylib::WHITE);
                    TilePosXY = m_Environnement.getTile(236);
                    rectTile.x = TilePosXY.x;
                    rectTile.y = TilePosXY.y;

                    raylib::ImageDraw(&map[2], m_Environnement.m_Tileset,
                        rectTile,
                        raylib::Rectangle{ (float)(x * m_Environnement.m_TileSize), (float)(y * m_Environnement.m_TileSize), TileSizeXY.x,TileSizeXY.y },
                        raylib::WHITE);
                    break;
                case 14: // Porte  Verttical Lock
                    // 2 x blocks
                    TilePosXY = m_Environnement.getTile(215);
                    rectTile.x = TilePosXY.x;
                    rectTile.y = TilePosXY.y;

                    raylib::ImageDraw(&map[2], m_Environnement.m_Tileset,
                        rectTile,
                        raylib::Rectangle{ (float)((x)*m_Environnement.m_TileSize), (float)((y - 1) * m_Environnement.m_TileSize), TileSizeXY.x,TileSizeXY.y },
                        raylib::WHITE);
                    TilePosXY = m_Environnement.getTile(235);
                    rectTile.x = TilePosXY.x;
                    rectTile.y = TilePosXY.y;

                    raylib::ImageDraw(&map[2], m_Environnement.m_Tileset,
                        rectTile,
                        raylib::Rectangle{ (float)(x * m_Environnement.m_TileSize), (float)(y * m_Environnement.m_TileSize), TileSizeXY.x,TileSizeXY.y },
                        raylib::WHITE);
                    break;
                case 15: // Porte Verttical Blocké
                    // 1 x block
                    TilePosXY = m_Environnement.getTile(288);
                    rectTile.x = TilePosXY.x;
                    rectTile.y = TilePosXY.y;

                    raylib::ImageDraw(&map[2], m_Environnement.m_Tileset,
                        rectTile,
                        raylib::Rectangle{ (float)(x * m_Environnement.m_TileSize), (float)(y * m_Environnement.m_TileSize), TileSizeXY.x,TileSizeXY.y },
                        raylib::WHITE);
                    break;
            }


        }
    }
    mapColorCollision = raylib::LoadImageColors(mapCollision);
}

void Dungeon_map::Init()
{
}

void Dungeon_map::LoadSprites()
{
  

}


Dungeon_map::~Dungeon_map()
{
    raylib::UnloadImage(map[0]);
    raylib::UnloadImage(map[2]);
}
