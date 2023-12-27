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
    int size_x=d["cells"].Capacity();
    int size_y = d["cells"][0].Capacity();
    int test = sizeof(unsigned long long);
    map = raylib::GenImageColor(size_x*48, size_y*48, raylib::BLANK);
    
     //raylib::DrawRectangleLines(x * 48, y * 48, 48, 48, raylib::GRAY);

    raylib::ImageDraw(&map, m_Environnement.m_Tileset, raylib::Rectangle{0, 0, 48.0f, 48.0f}, raylib::Rectangle{0, 0, 48.0f, 48.0f}, raylib::GRAY);

}

Dungeon_map::~Dungeon_map()
{
    raylib::UnloadImage(map);
}
