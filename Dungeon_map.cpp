#include "Dungeon_map.h"



std::vector<std::string> Dungeon_map::GetListMonsters(std::string& substr, std::string& str)
{
    int occurrences = 0;
    std::string::size_type pos = 0;
    std::string::size_type posPrec = 0;
    std::vector<std::string> retourList;
    std::vector<int> occurPosList;
    occurPosList.push_back(0);

    while ((pos = str.find(substr, pos)) != std::string::npos) {
        ++occurrences;
        pos += substr.length();

        occurPosList.push_back(pos);
    }

    for (int occurPos = 0; occurPos < (occurPosList.capacity()); occurPos++)
    {
        int pos_debut = occurPosList.at(occurPos);
        int pos_fin = 0;
        if (occurPos < (occurPosList.capacity() - 1))
        {
            pos_fin = occurPosList.at(occurPos + 1) - occurPosList.at(occurPos) - substr.length();;
        }
        else
        {
            pos_fin = str.length();
        }
        retourList.push_back(str.substr(pos_debut, pos_fin));
    }

    return  retourList;
}
int Dungeon_map::GetNbMonster(std::string& str)
{
    int occurrences = 0;
    std::string::size_type pos = 0;
    for (std::string Coeff : m_Coeff)
    {
        occurrences++;
        pos = str.find(Coeff, 0);
        if (pos != std::string::npos)
        {
            return occurrences;
        }

    }
    return  1;
}
Dungeon_map::Dungeon_map()
{
    // Chargement TileSet
    m_Environnement.Init();
    // Chargement des Sprites
    LoadSprites();

    std::ifstream ifs{ R"(Resources/donjon/The Tomb of Shadowy Death 01.json )" }; 
    //The Sanctum of Shadowy Nightmares 01.json   --> moyen
    //The Tomb of Shadowy Death 01.json   --> petite
    //The Forsaken Cyst of Doom 01.json   --> enorme
    if (!ifs.is_open())
    {
        std::cerr << "Could not open file for reading!\n";
        exit(0);
    }

    IStreamWrapper isw{ ifs };
    d.ParseStream(isw);
    size_y = d["cells"].Capacity();
    size_x = d["cells"][0].Capacity();
    mapBrute = new int[size_x* size_y];

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

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // JSON
    // Enregistrement du nombre de clé ou bombe pour quitter une room
    Logger::GetInstance()->Log(__FILE__, __LINE__, "---- JSON ----------------------------------------", LogLevel::INFO);
    Logger::GetInstance()->Log(__FILE__, __LINE__, "Faut il une clé pour quitter la room : ", LogLevel::INFO);
    for (int indexRoom = 1; indexRoom < d["rooms"].Capacity(); indexRoom++)  // La Room 0, n'existe jamais
    {
        struct s_typePortesRoom TypePortesRoom;
        TypePortesRoom.NbPorteLocker = 0;
        TypePortesRoom.NbPorteSecret=0;
        TypePortesRoom.id_Room = indexRoom;
        assert(d["rooms"][indexRoom]["col"].IsInt());
        TypePortesRoom.Room.x = d["rooms"][indexRoom]["col"].GetInt();
        assert(d["rooms"][indexRoom]["row"].IsInt());
        TypePortesRoom.Room.y = d["rooms"][indexRoom]["row"].GetInt();
        assert(d["rooms"][indexRoom]["height"].IsInt());
        TypePortesRoom.Room.height = d["rooms"][indexRoom]["height"].GetInt() / 10;
        assert(d["rooms"][indexRoom]["width"].IsInt());
        TypePortesRoom.Room.width = d["rooms"][indexRoom]["width"].GetInt() / 10;
        assert(d["rooms"][indexRoom].IsObject());
        if ((d["rooms"][indexRoom].HasMember("doors") == true))
        {
            assert(d["rooms"][indexRoom]["doors"].IsObject());
            if ((d["rooms"][indexRoom]["doors"].HasMember("north") == true))
            {
                assert(d["rooms"][indexRoom]["doors"]["north"].IsArray());
                int nb = d["rooms"][indexRoom]["doors"]["north"].Capacity();
                for (int indexDoor=0; indexDoor <nb; indexDoor++)
                {
                    assert(d["rooms"][indexRoom]["doors"]["north"][indexDoor].IsObject());
                    assert(d["rooms"][indexRoom]["doors"]["north"][indexDoor]["type"].IsString());
                    std::string typeStr = d["rooms"][indexRoom]["doors"]["north"][indexDoor]["type"].GetString();
                    if (typeStr == "locked")
                    {
                        TypePortesRoom.NbPorteLocker++;
                    }
                    if (typeStr == "secret")
                    {
                        TypePortesRoom.NbPorteSecret++;
                    }
                }

            }
            if ((d["rooms"][indexRoom]["doors"].HasMember("south") == true))
            {
                assert(d["rooms"][indexRoom]["doors"]["south"].IsArray());
                int nb = d["rooms"][indexRoom]["doors"]["south"].Capacity();
                for (int indexDoor = 0; indexDoor < nb; indexDoor++)
                {
                    assert(d["rooms"][indexRoom]["doors"]["south"][indexDoor].IsObject());
                    assert(d["rooms"][indexRoom]["doors"]["south"][indexDoor]["type"].IsString());
                    std::string typeStr = d["rooms"][indexRoom]["doors"]["south"][indexDoor]["type"].GetString();
                    if (typeStr == "locked")
                    {
                        TypePortesRoom.NbPorteLocker++;
                    }
                    if (typeStr == "secret")
                    {
                        TypePortesRoom.NbPorteSecret++;
                    }
                }


            }

            if ((d["rooms"][indexRoom]["doors"].HasMember("west") == true))
            {
                assert(d["rooms"][indexRoom]["doors"]["west"].IsArray());
                int nb = d["rooms"][indexRoom]["doors"]["west"].Capacity();
                for (int indexDoor = 0; indexDoor < nb; indexDoor++)
                {
                    assert(d["rooms"][indexRoom]["doors"]["west"][indexDoor].IsObject());
                    assert(d["rooms"][indexRoom]["doors"]["west"][indexDoor]["type"].IsString());
                    std::string typeStr = d["rooms"][indexRoom]["doors"]["west"][indexDoor]["type"].GetString();
                    if (typeStr == "locked")
                    {
                        TypePortesRoom.NbPorteLocker++;
                    }
                    if (typeStr == "secret")
                    {
                        TypePortesRoom.NbPorteSecret++;
                    }
                }


            }

            if ((d["rooms"][indexRoom]["doors"].HasMember("east") == true))
            {
                assert(d["rooms"][indexRoom]["doors"]["east"].IsArray());
                int nb = d["rooms"][indexRoom]["doors"]["east"].Capacity();
                for (int indexDoor = 0; indexDoor < nb; indexDoor++)
                {
                    assert(d["rooms"][indexRoom]["doors"]["east"][indexDoor].IsObject());
                    assert(d["rooms"][indexRoom]["doors"]["east"][indexDoor]["type"].IsString());
                    std::string typeStr = d["rooms"][indexRoom]["doors"]["east"][indexDoor]["type"].GetString();
                    if (typeStr == "locked")
                    {
                        TypePortesRoom.NbPorteLocker++;
                    }
                    if (typeStr == "secret")
                    {
                        TypePortesRoom.NbPorteSecret++;
                    }
                }

            }

            

                
                
        }
        if ((TypePortesRoom.NbPorteLocker!=0) || (TypePortesRoom.NbPorteSecret!=0))
        {
            m_ListsTypePortesRoom.push_back(TypePortesRoom);
        }

    }
    Logger::GetInstance()->Log(__FILE__, __LINE__, "--> Nb Room avec des portes particulieres : "+std::to_string(m_ListsTypePortesRoom.capacity()), LogLevel::INFO);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // JSON
    // Enregistrement du nombre de monstres
    Logger::GetInstance()->Log(__FILE__, __LINE__, "---- JSON ----------------------------------------", LogLevel::INFO);
    Logger::GetInstance()->Log(__FILE__, __LINE__, "Recuperation de la Liste des Monstres : ", LogLevel::INFO);
    int idMonstre = 0;
    for (int index = 1; index < d["rooms"].Capacity(); index++)  // La Room 0, n'existe jamais
    {
        assert(d["rooms"][index].IsObject());

        assert(d["rooms"][index]["contents"].IsObject());
        if ((d["rooms"][index]["contents"].HasMember("inhabited")==true))
        {
            assert(d["rooms"][index]["contents"]["inhabited"].IsString());
            Logger::GetInstance()->Log(__FILE__, __LINE__, std::string(d["rooms"][index]["contents"]["inhabited"].GetString()), LogLevel::INFO);
            std::string RoomMonsters(d["rooms"][index]["contents"]["inhabited"].GetString());
            std::vector<std::string> ListRoomMonster;
            // combien y a t il de "and" pour séparé les monstres dans une liste
            std::string AndWord=" and ";
            ListRoomMonster =GetListMonsters(AndWord, RoomMonsters);
 
            for (std::string RoomMonster : ListRoomMonster)
            {
                struct s_monstres Monster;
                Monster.NbMonster = GetNbMonster(RoomMonster);
                Monster.id_Room = index;
                Monster.NomMonster = RoomMonster;
                Monster.id_monstre = idMonstre;
                idMonstre= (idMonstre+1)%7;
                assert(d["rooms"][index]["col"].IsInt());
                Monster.Room.x = d["rooms"][index]["col"].GetInt();
                assert(d["rooms"][index]["row"].IsInt());
                Monster.Room.y = d["rooms"][index]["row"].GetInt();
                assert(d["rooms"][index]["height"].IsInt());
                Monster.Room.height = d["rooms"][index]["height"].GetInt()/10;
                assert(d["rooms"][index]["width"].IsInt());
                Monster.Room.width = d["rooms"][index]["width"].GetInt()/10;
                Monster.GiveKey = 0;

                Logger::GetInstance()->Log(__FILE__, __LINE__, " - "+RoomMonster+"("+std::to_string(Monster.NbMonster) + ")", LogLevel::INFO);
                m_ListMonstres.push_back(Monster);

            }
        }
    }
    Logger::GetInstance()->Log(__FILE__, __LINE__, "--> Nb Room avec des monstres : " + std::to_string(m_ListMonstres.capacity()), LogLevel::INFO);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // JSON
    // Enregistrement du nombre de tresores
    Logger::GetInstance()->Log(__FILE__, __LINE__, "---- JSON ----------------------------------------", LogLevel::INFO);
    Logger::GetInstance()->Log(__FILE__, __LINE__, "Recuperation de la Liste des Tresors : ", LogLevel::INFO);
    for (int index = 1; index < d["rooms"].Capacity(); index++)  // La Room 0, n'existe jamais
    {
        assert(d["rooms"][index].IsObject());
        assert(d["rooms"][index]["contents"].IsObject());
        if ((d["rooms"][index]["contents"].HasMember("detail") == true))
        {
            assert(d["rooms"][index]["contents"]["detail"].IsObject());
            if ((d["rooms"][index]["contents"]["detail"].HasMember("monster") == true))
            {
                assert(d["rooms"][index]["contents"]["detail"]["monster"].IsArray());

                Logger::GetInstance()->Log(__FILE__, __LINE__, std::string(d["rooms"][index]["contents"]["detail"]["monster"][2].GetString()), LogLevel::INFO);
                struct s_tresors Tresor;
                Tresor.id_Room = index;
                Tresor.NomTresors = std::string(d["rooms"][index]["contents"]["detail"]["monster"][2].GetString());
                assert(d["rooms"][index]["col"].IsInt());
                Tresor.Room.x = d["rooms"][index]["col"].GetInt();
                assert(d["rooms"][index]["row"].IsInt());
                Tresor.Room.y = d["rooms"][index]["row"].GetInt();
                assert(d["rooms"][index]["height"].IsInt());
                Tresor.Room.height = d["rooms"][index]["height"].GetInt() / 10;
                assert(d["rooms"][index]["width"].IsInt());
                Tresor.Room.width = d["rooms"][index]["width"].GetInt() / 10;
                m_ListTresors.push_back(Tresor);

            }
        }
    }
    Logger::GetInstance()->Log(__FILE__, __LINE__, "--> Nb Room avec des Tresors : " + std::to_string(m_ListTresors.capacity()), LogLevel::INFO);
    for (struct s_tresors Tresor : m_ListTresors)
    {
        //Ajout Tresor to InteractObject
        Block_Interact Block{};
        int x = Tresor.Room.x+1;
        int y = Tresor.Room.y+1;
        Block.Box.x = (float)(x * m_Environnement.m_TileSize);
        Block.Box.y = (float)(y * m_Environnement.m_TileSize);
        Block.Box.width = TileSizeXY.x;
        Block.Box.height = TileSizeXY.y;
        Block.Etat = 0;
        Block.Type = 6;// Tresors
        Block.x = x;
        Block.y = y;
        if (Block.Type >= 0)
        {
            CollisionMap.push_back(Block);
        }
    }


    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // JSON
    // Coordonnees d'entrees et de sorties
    Logger::GetInstance()->Log(__FILE__, __LINE__, "---- JSON ----------------------------------------", LogLevel::INFO);
    Logger::GetInstance()->Log(__FILE__, __LINE__, "Recuperation des coordonnées d'Entrée et de Sotrie : ", LogLevel::INFO);
    Entree.x = 0;
    Entree.y = 0;
    Sortie.x = 0;
    Sortie.y = 0;
    if ((d.HasMember("stairs") == true))
    {
        assert(d["stairs"].IsArray());
        for (int index = 0; index < d["stairs"].Capacity(); index++)
        {
            int length = d["stairs"][index]["key"].GetStringLength();
            if (length > 0)
            {
                // Entree
                if (d["stairs"][index]["key"].GetString()[0] == 'd')
                {
                    Entree.x = d["stairs"][index]["col"].GetInt();
                    Entree.y = d["stairs"][index]["row"].GetInt();
                }
                // Sortie
                if (d["stairs"][index]["key"].GetString()[0] == 'u')
                {
                    Sortie.x = d["stairs"][index]["col"].GetInt();
                    Sortie.y = d["stairs"][index]["row"].GetInt();
                }
            }
        }
    }
    if ((Entree.x==0) || (Sortie.x==0))
    {
        std::cerr << "Impossible de trouver l'entree ou la sortie sur le fichier JSON\n";
        exit(0);
    }
   
    //Couche N°0 (Couche Fixe) mur + sol
    for (int x = 0; x < size_x; x++)
    {
        for (int y = 0; y < size_y; y++)
        {
            mapBrute[x + y * size_x] = 0;
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

            
            //InteractObject
            Block_Interact Block{};
            Block.Box.x = (float)(x * m_Environnement.m_TileSize);
            Block.Box.y = (float)(y * m_Environnement.m_TileSize);
            Block.Box.width =  TileSizeXY.x;
            Block.Box.height =  TileSizeXY.y;
            Block.Etat = 0;
            Block.Type = m_Environnement.m_Block.TypeOfInteractObject(d["cells"][y][x].GetInt64(),
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
            mapBrute[x + y * size_x] = m_Environnement.m_Block.getTilesetBlock(d["cells"][y][x].GetInt64());

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
                    // Morceau de l'escalier montant de la sortie
                    if (block == 328)
                    {
                        TilePosXY = m_Environnement.getTile(308);

                        rectTile.x = TilePosXY.x;
                        rectTile.y = TilePosXY.y;

                        raylib::ImageDraw(&map[1], m_Environnement.m_Tileset,
                            rectTile,
                            raylib::Rectangle{ (float)(x * m_Environnement.m_TileSize), (float)((y-1) * m_Environnement.m_TileSize), TileSizeXY.x,TileSizeXY.y },
                            raylib::WHITE);
                    }
                    else
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

    }
 
    //Couche N°3 (ouverture(Arche))
    for (int x = 0; x < size_x; x++)
    {
        for (int y = 0; y < size_y; y++)
        {

            int type_ouverture = m_Environnement.m_Block.TypeOfInteractObject(d["cells"][y][x].GetInt64(),
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
    int index = 0;
    Block_Interact boxTempo;

    for (Block_Interact box : CollisionMap)
    {
        
        if (box.Type != 3) // 3 = Arch ==> l'arch n'est pas un mur
        {
            if (raylib::CheckCollisionRecs(hero, box.Box) == true)
            {
                if ((box.Type == 1) || (box.Type == 2))
                {
                    // Fin immediatement
                    Collbox = box;
                    return true;
                }
                else
                {
                    // on attend eventuellemnt une porte dans une 2 eme collision
                    boxTempo = box;
                    index++;
                }
                if (index == 2)
                {
                    // au bout de 2 collisions on arrete
                    Collbox = box;
                    return true;
                }
            }
        }
    }
    // si pas de 2eme collision
    if (index != 0)
    {
        Collbox = boxTempo;
        return true;
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
