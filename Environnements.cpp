#include "Logger.h"
#include "Environnements.h"


Environnements::Environnements()
{


}

void Environnements::initEnvironnements()
{
	
	m_Tileset = raylib::LoadImage("Resources/environnements/tilset_1/tiles_dungeon_v1.1_48x48.png");     // Loaded in CPU memory (RAM)
	if (m_Tileset.height == 0)
	{
		//erreur
		Logger::GetInstance()->Log(__FILE__, __LINE__, "Erreur de chargement du TileSet : tiles_dungeon_v1.1_48x48.png", LogLevel::ERROR);
		return;
	}
	m_TileSize = 48;
	m_sizeTileSet_x = 20;
	m_sizeTileSet_y = 24;
}

Environnements::~Environnements()
{
	raylib::UnloadImage(m_Tileset);
}

raylib::Vector2 Environnements::getTile(int index)
{

	return raylib::Vector2{ (float)((index % m_sizeTileSet_x) * m_TileSize),(float)((index / m_sizeTileSet_x) * m_TileSize) };
}
