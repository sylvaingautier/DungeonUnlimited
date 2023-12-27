#include "Logger.h"
#include "Environnements.h"


Environnements::Environnements()
{


}

void Environnements::initEnvironnements()
{
	m_Tileset = raylib::LoadImage("Resources/environnements/Dungeon tileset.png");     // Loaded in CPU memory (RAM)
	if (m_Tileset.height == 0)
	{
		//erreur
		Logger::GetInstance()->Log(__FILE__, __LINE__, "Erreur de chargement du TileSet : Dungeon tileset.png", LogLevel::ERROR);
		return;
	}
	texture = raylib::LoadTextureFromImage(m_Tileset);


}

Environnements::~Environnements()
{
	raylib::UnloadImage(m_Tileset);
}
