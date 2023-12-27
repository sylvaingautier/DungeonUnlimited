#pragma once
#include "Logger.h"
#include <fstream>
#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>

using namespace rapidjson;

class Dungeon_map
{

public:
	enum e_porte
	{
		EMPTY = 0,
		NORMAL = 1,
		ARCHWAY = 2,
		STAIRS = 3,
		PORTCULLIS = 4,
		SPECIAL = 5,
		SECRET = 6,
		BARRED = 7,
		EXIT = 8,
		STEPS = 9

	};
public:
	rapidjson::Document d;
	Dungeon_map();


};