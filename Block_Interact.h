#pragma once

namespace raylib {
#include "raylib.h"
}
class Block_Interact
{
public:
		raylib::Rectangle Box;
		int Type; //0=mur ==> pas de id
		//1=porte // grille sans cl�
		//2=porte � verou 
		int Etat; //0=Coffret ferm�e
		//1=Coffret Ouvert
		int x;
		int y;
		bool operator==(const Block_Interact&);
	
};

