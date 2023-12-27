#include "Dungeon_map.h"


Dungeon_map::Dungeon_map()
{
    std::ifstream ifs{ R"(Resources/donjon/donjon_1.json)" };
    if (!ifs.is_open())
    {
        std::cerr << "Could not open file for reading!\n";
        return;
    }

    IStreamWrapper isw{ ifs };
    d.ParseStream(isw);
    int test=d["rects"].Capacity();



}
