#pragma once
#include "Logger.h"
#include <fstream>
#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>
#include "Environnements.h"


namespace raylib {
#include "raylib.h"
}
using namespace rapidjson;

class Dungeon_map
{
	/*
my $NOTHING     = 0x00000000;

my $BLOCKED     = 0x00000001;
my $ROOM        = 0x00000002;
my $CORRIDOR    = 0x00000004;
#                 0x00000008;
my $PERIMETER   = 0x00000010;
my $ENTRANCE    = 0x00000020;
my $ROOM_ID     = 0x0000FFC0;

my $ARCH        = 0x00010000;
my $DOOR        = 0x00020000;
my $LOCKED      = 0x00040000;
my $TRAPPED     = 0x00080000;
my $SECRET      = 0x00100000;
my $PORTC       = 0x00200000;
my $STAIR_DN    = 0x00400000;
my $STAIR_UP    = 0x00800000;

my $LABEL       = 0xFF000000;

my $OPENSPACE   = $ROOM | $CORRIDOR;
my $DOORSPACE   = $ARCH | $DOOR | $LOCKED | $TRAPPED | $SECRET | $PORTC;
my $ESPACE      = $ENTRANCE | $DOORSPACE | 0xFF000000;
my $STAIRS      = $STAIR_DN | $STAIR_UP;

my $BLOCK_ROOM  = $BLOCKED | $ROOM;
my $BLOCK_CORR  = $BLOCKED | $PERIMETER | $CORRIDOR;
my $BLOCK_DOOR  = $BLOCKED | $DOORSPACE;*/


public:
	raylib::Image map[4];
	Environnements m_Environnement;
public:
	rapidjson::Document d;
	Dungeon_map();
	~Dungeon_map();

};
