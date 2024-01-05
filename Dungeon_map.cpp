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
    size_y = d["cells"].Capacity();
    size_x = d["cells"][0].Capacity();
    sizeMapPixels_x = size_x * 48;
    sizeMapPixels_y = size_y * 48;
    map[0] = raylib::GenImageColor(size_x * 48, size_y * 48, raylib::BLANK);
    map[1] = raylib::GenImageColor(size_x * 48, size_y * 48, raylib::BLANK);
    map[2] = raylib::GenImageColor(size_x * 48, size_y * 48, raylib::BLANK);
    map[3] = raylib::GenImageColor(size_x * 48, size_y * 48, raylib::BLANK);
    PrecipiceMap = raylib::GenImageColor(size_x * 48, size_y * 48, raylib::BLANK);

    raylib::Vector2 TileSizeXY;
    TileSizeXY.x = (float)m_Environnement.m_TileSize;
    TileSizeXY.y = (float)m_Environnement.m_TileSize;

    raylib::Vector2 TilePosXY;
    TilePosXY.x = 0;
    TilePosXY.y = 0;

    raylib::Rectangle rectTile{};
    rectTile.height = TileSizeXY.x;
    rectTile.width = TileSizeXY.y;

    //Couche N°0 (Couche Fixe) mur + sol
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
            Block_Interact Block{};
            Block.Box.x = (float)(x * m_Environnement.m_TileSize);
            Block.Box.y = (float)(y * m_Environnement.m_TileSize);
            Block.Box.width =  TileSizeXY.x;
            Block.Box.height =  TileSizeXY.y;
            Block.Etat = 0;
            Block.Type = m_Environnement.m_Block.isDoor(d["cells"][y][x].GetInt64(),
                (y == 0) ? 0 : d["cells"][y - 1][x].GetInt64(),
                (y == (size_y - 1)) ? 0 : d["cells"][y + 1][x].GetInt64(),
                (x == 0) ? 0 : d["cells"][y][x - 1].GetInt64(),
                (x == (size_x - 1)) ? 0 : d["cells"][y][x + 1].GetInt64());
            Block.x =  x;
            Block.y = y;
            if (Block.Type >= 0)
            {
                CollisionMap.push_back(Block);
            }
            //PrecipiceMap
            if (m_Environnement.m_Block.getBlockType(d["cells"][y][x].GetInt64())==0)
            {
                raylib::ImageDrawRectangle(&PrecipiceMap, (float)(x * m_Environnement.m_TileSize), (float)(y * m_Environnement.m_TileSize), 48,48, raylib::WHITE);
            }

        }
    }
    PrecipiceMapColor = raylib::LoadImageColors(PrecipiceMap);
    //Couche N°1 (Details Couche Fixe) mur + sol
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
 
    //Couche N°3 (ouverture(Arche))
    for (int x = 0; x < size_x; x++)
    {
        for (int y = 0; y < size_y; y++)
        {

            int type_ouverture = m_Environnement.m_Block.isDoor(d["cells"][y][x].GetInt64(),
                (y == 0) ? 0 : d["cells"][y - 1][x].GetInt64(),
                (y == (size_y - 1)) ? 0 : d["cells"][y + 1][x].GetInt64(),
                (x == 0) ? 0 : d["cells"][y][x - 1].GetInt64(),
                (x == (size_x - 1)) ? 0 : d["cells"][y][x + 1].GetInt64());

            switch (type_ouverture)
            {
            case 3: // Arch Horizontal
                // 6 x block
                TilePosXY = m_Environnement.getTile(240);
                rectTile.x = TilePosXY.x;
                rectTile.y = TilePosXY.y;

                raylib::ImageDraw(&map[3], m_Environnement.m_Tileset,
                    rectTile,
                    raylib::Rectangle{ (float)((x - 1) * m_Environnement.m_TileSize), (float)((y - 1) * m_Environnement.m_TileSize), TileSizeXY.x,TileSizeXY.y },
                    raylib::WHITE);
                TilePosXY = m_Environnement.getTile(260);
                rectTile.x = TilePosXY.x;
                rectTile.y = TilePosXY.y;

                raylib::ImageDraw(&map[3], m_Environnement.m_Tileset,
                    rectTile,
                    raylib::Rectangle{ (float)((x - 1) * m_Environnement.m_TileSize), (float)(y * m_Environnement.m_TileSize), TileSizeXY.x,TileSizeXY.y },
                    raylib::WHITE);

                TilePosXY = m_Environnement.getTile(241);
                rectTile.x = TilePosXY.x;
                rectTile.y = TilePosXY.y;

                raylib::ImageDraw(&map[3], m_Environnement.m_Tileset,
                    rectTile,
                    raylib::Rectangle{ (float)(x * m_Environnement.m_TileSize), (float)((y - 1) * m_Environnement.m_TileSize), TileSizeXY.x,TileSizeXY.y },
                    raylib::WHITE);
                TilePosXY = m_Environnement.getTile(261);
                rectTile.x = TilePosXY.x;
                rectTile.y = TilePosXY.y;

                raylib::ImageDraw(&map[3], m_Environnement.m_Tileset,
                    rectTile,
                    raylib::Rectangle{ (float)(x * m_Environnement.m_TileSize), (float)(y * m_Environnement.m_TileSize), TileSizeXY.x,TileSizeXY.y },
                    raylib::WHITE);
                TilePosXY = m_Environnement.getTile(242);
                rectTile.x = TilePosXY.x;
                rectTile.y = TilePosXY.y;

                raylib::ImageDraw(&map[3], m_Environnement.m_Tileset,
                    rectTile,
                    raylib::Rectangle{ (float)((x + 1) * m_Environnement.m_TileSize), (float)((y - 1) * m_Environnement.m_TileSize), TileSizeXY.x,TileSizeXY.y },
                    raylib::WHITE);
                TilePosXY = m_Environnement.getTile(262);
                rectTile.x = TilePosXY.x;
                rectTile.y = TilePosXY.y;

                raylib::ImageDraw(&map[3], m_Environnement.m_Tileset,
                    rectTile,
                    raylib::Rectangle{ (float)((x + 1) * m_Environnement.m_TileSize), (float)(y * m_Environnement.m_TileSize), TileSizeXY.x,TileSizeXY.y },
                    raylib::WHITE);
                break;
 
            }


        }
    }

}

bool Dungeon_map::isCollisionMap(raylib::Rectangle hero, Block_Interact&Collbox)
{
    for (Block_Interact box : CollisionMap)
    {
        if (box.Type != 3) // 3 = Arch ==> l'arch n'est pas un mur
        {
            if (raylib::CheckCollisionRecs(hero, box.Box) == true)
            {
                Collbox = box;
                return true;
            }
        }
    }
    return false;
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
