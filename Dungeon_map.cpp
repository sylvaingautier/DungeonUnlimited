#include "Dungeon_map.h"


Dungeon_map::Dungeon_map()
{
    m_Environnement.initEnvironnements();

    std::ifstream ifs{ R"(Resources/donjon/The Dark Crypts of the Lich Princess 01.json)" };
    if (!ifs.is_open())
    {
        std::cerr << "Could not open file for reading!\n";
        return;
    }

    IStreamWrapper isw{ ifs };
    d.ParseStream(isw);
    int size_y = d["cells"].Capacity();
    int size_x = d["cells"][0].Capacity();
    map = raylib::GenImageColor(size_y * 48, size_x * 48, raylib::BLANK);
    raylib::Vector2 TileSizeXY;
    TileSizeXY.x = (float)m_Environnement.m_TileSize;
    TileSizeXY.y = (float)m_Environnement.m_TileSize;
    
    raylib::Vector2 TilePosXY;
    TilePosXY.x = 0;
    TilePosXY.y = 0;
    
    raylib::Rectangle rectTile;
    rectTile.height = TileSizeXY.x;
    rectTile.width = TileSizeXY.y;

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

            raylib::ImageDraw(&map, m_Environnement.m_Tileset,
                rectTile,
                raylib::Rectangle{ (float)(x* m_Environnement.m_TileSize), (float)(y* m_Environnement.m_TileSize), TileSizeXY.x,TileSizeXY.y },
                raylib::GRAY);
        }
    }
    
     //raylib::DrawRectangleLines(x * 48, y * 48, 48, 48, raylib::GRAY);
    //raylib::ImageDraw(&map, m_Environnement.m_Tileset, raylib::Rectangle{ 0, 0, 48.0f, 48.0f }, raylib::Rectangle{ 48, 48, 48.0f, 48.0f }, raylib::GRAY);
}

Dungeon_map::~Dungeon_map()
{
    raylib::UnloadImage(map);
}
