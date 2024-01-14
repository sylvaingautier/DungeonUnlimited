#pragma once
#include "Logger.h"
#include <fstream>
#include <iostream>
#include <string>

#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>
#include "Environnements.h"
#include "monstre.h"

namespace raylib {
#include "raylib.h"
}
using namespace rapidjson;

class Dungeon_map
{

public:
	const std::string m_Coeff[9]
		= { "1 x ",
			"2 x ",
			"3 x ",
			"4 x ",
			"5 x ",
			"6 x ",
			"7 x ",
			"8 x ",
			"9 x " };

	raylib::Image map[4];
	//0=rien ou precipisse
	int *mapBrute;
	raylib::Image PrecipiceMap;
	raylib::Color* PrecipiceMapColor;
	std::vector <Block_Interact> CollisionMap;
	int sizeMapPixels_x;
	int sizeMapPixels_y;
	int size_y;
	int size_x;
	raylib::Vector2 Entree,Sortie;
	Environnements m_Environnement;
	struct s_liste_block
	{
		std::vector<int> Block;

	};
	struct s_monstres
	{
		std::string NomMonster;
		int NbMonster;
		int id_monstre;
		int id_Room;
		bool GiveKey;
		raylib::Rectangle Room;
	};

	std::vector<struct s_monstres> m_ListMonstres;
	struct s_tresors
	{
		std::string NomTresors;
		int id_Room;

		raylib::Rectangle Room;
	};
	std::vector<struct s_tresors> m_ListTresors;

	struct s_typePortesRoom
	{
		int id_Room;
		int NbPorteSecret;
		int NbPorteLocker;

		raylib::Rectangle Room;
	};

	std::vector<struct s_typePortesRoom> m_ListsTypePortesRoom;

public:
	rapidjson::Document d;
	void SearchingMonster(const char* monstre);
	std::vector<std::string> GetListMonsters(std::string& substr, std::string& str);
	int GetNbMonster(std::string& str);
	Dungeon_map();
	bool isCollisionMap(raylib::Rectangle hero, Block_Interact& Collbox);
	void Init();
	void LoadSprites();
	~Dungeon_map();


};
