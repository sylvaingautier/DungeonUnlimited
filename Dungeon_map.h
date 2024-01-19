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
	int m_pattern_3_3Nb = 2;
	const int m_pattern_3_3[9*6] 
		= { 9 ,10,11, //1
	        29,30,31,
	        49,50,51,
		    0,1,2,     //2
		    20,21,22,
		    40,41,42,
		    80,81,82,   //3
		    100,101,102,
		    120,121,122,
		    89,90,91,   //4
	        109,110,111,
	        129,130,131,
	         172,173,172, //5
		     192,193,192,
		     172,173,172,
	         1,9,1,       //6
		     5,7,8,
		     1,9,1};

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
