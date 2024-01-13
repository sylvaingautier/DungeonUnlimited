#pragma once
#include "Dungeon_map.h"
#include <array> 

namespace raylib {
#include "raylib.h"
}
#include "hero.h"

class GameCore
{
public:
	//----------------------------------------------------------------------------------
	// Local Variables Definition (local to this module)
	//----------------------------------------------------------------------------------
	static const int SCREENWIDTH = 1280;
	static const int SCREENHEIGHT = 720;
	Dungeon_map TheDungeon;
	Hero hero;
    std::vector <Monstre> LesMonstres;

	static const int NB_TILESETMONSTER = 7;
	// Monstres
	std::array<std::string, NB_TILESETMONSTER> m_TilesetMonster=
	{"Resources/personnages/chara_troll_48x48.png",
	"Resources/personnages/chara_bat_48x48.png",
	"Resources/personnages/chara_goblin_48x48.png",
	"Resources/personnages/chara_orc_48x48.png",
	"Resources/personnages/chara_rat_48x48.png",
	"Resources/personnages/chara_slime_48x48.png",
	"Resources/personnages/chara_spider_48x48.png"};
	raylib::Texture2D texMonstre[NB_TILESETMONSTER];
	raylib::Texture2D texMonstre_Flip_Horizontal[NB_TILESETMONSTER];


	raylib::Vector2 map_pos_in_screen{};
	raylib::Texture2D texTileSet;
	raylib::Texture2D texMap0;
	raylib::Texture2D texMap1;
	raylib::Texture2D texMap3;
	raylib::Texture2D texHero;
	raylib::Texture2D texHero_Flip_Horizontal;

	raylib::Texture2D texPrecipiceMap;
public:
	GameCore();
	void initGameCore();
	void endGameCore();
	void loopGameCore();
	void MortDuHero(int type);
	void DrawMonsters();
	void IAMonster();
	void DrawDetails();
	void DrawSortie();

};

