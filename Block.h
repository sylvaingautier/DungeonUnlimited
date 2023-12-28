#pragma once
#include "Randomer.h"
namespace raylib {
#include "raylib.h"
}

class Block
{
public:
	enum Enum_type_dungeon_generator
	{
		NOTHING = 0x00000000,
		BLOCKED = 0x00000001,
		ROOM = 0x00000002,
		CORRIDOR = 0x00000004,
		PERIMETER = 0x00000010,
		ENTRANCE = 0x00000020,
		ROOM_ID = 0x0000FFC0,
		ARCH = 0x00010000,
		DOOR = 0x00020000,
		LOCKED = 0x00040000,
		TRAPPED = 0x00080000,
		SECRET = 0x00100000,
		PORTC = 0x00200000,
		STAIR_DN = 0x00400000,
		STAIR_UP = 0x00800000,
		LABEL = 0xFF000000,
		OPENSPACE = ROOM | CORRIDOR,
		DOORSPACE = ARCH | DOOR | LOCKED | TRAPPED | SECRET | PORTC,
		ESPACE = ENTRANCE | DOORSPACE | 0xFF000000,
		STAIRS = STAIR_DN | STAIR_UP,
		BLOCK_ROOM = BLOCKED | ROOM,
		BLOCK_CORR = BLOCKED | PERIMETER | CORRIDOR,
		BLOCK_DOOR = BLOCKED | DOORSPACE
	};
	enum Enum_type_tileset
	{
		VIDE = 60,

	};

public:
	Block();
	~Block();
	int getTilesetBlock(int couche, long long centre, long long haut, long long bas, long long gauche, long long droite);
	int porte(long long haut, long long bas, long long gauche, long long droite);
	int mur(long long haut, long long bas, long long gauche, long long droite);


	int sol(long long haut, long long bas, long long gauche, long long droite);
	int vide(long long haut, long long bas, long long gauche, long long droite);
};

