#include "Block.h"

Block::Block()
{
}

Block::~Block()
{
}

/// <summary>
/// 
/// </summary>
/// <param name="centre"></param>
/// <returns>0 = Rien ; 1 = Porte_H ; 2 = Grille_H ; 3 = Arche_H; 4 = Porte_H_LOCK ; 5 = porte blokée;  11 = Porte_V ; 12 = Grille_V ; 13 = Arche_V ; 14 = Porte_V_LOCK; 15 = porte blokée </returns>
int Block::isDoor(long long centre, long long haut, long long bas, long long gauche, long long droite)
{
	//C'est une ouverture Horizontal
	if ( (((haut & Enum_type_dungeon_generator::CORRIDOR) == Enum_type_dungeon_generator::CORRIDOR) || ((haut & Enum_type_dungeon_generator::ROOM) == Enum_type_dungeon_generator::ROOM))
		&&
		 (((bas & Enum_type_dungeon_generator::CORRIDOR) == Enum_type_dungeon_generator::CORRIDOR)  || ((bas & Enum_type_dungeon_generator::ROOM) == Enum_type_dungeon_generator::ROOM)) )
	{
		// Porte Horizontal
		if ((centre & Enum_type_dungeon_generator::DOOR) == Enum_type_dungeon_generator::DOOR)
		{
			return 1;
		}
		// Grille Horizontal
		if ((centre & Enum_type_dungeon_generator::PORTC) == Enum_type_dungeon_generator::PORTC)
		{
			return 2;
		}
		// Arche Horizontal
		if ((centre & Enum_type_dungeon_generator::ARCH) == Enum_type_dungeon_generator::ARCH)
		{
			return 3;
		}
		// Porte Horizontal Lock
		if ((centre & Enum_type_dungeon_generator::LOCKED) == Enum_type_dungeon_generator::LOCKED)
		{
			return 4;
		}
		// Porte Horizontal blocké Lock
		if ((centre & Enum_type_dungeon_generator::SECRET) == Enum_type_dungeon_generator::SECRET)
		{
			return 5;
		}
	}
	//C'est une ouverture Veticale
	if ((((gauche & Enum_type_dungeon_generator::CORRIDOR) == Enum_type_dungeon_generator::CORRIDOR) || ((gauche & Enum_type_dungeon_generator::ROOM) == Enum_type_dungeon_generator::ROOM))
		&&
		(((droite & Enum_type_dungeon_generator::CORRIDOR) == Enum_type_dungeon_generator::CORRIDOR) || ((droite & Enum_type_dungeon_generator::ROOM) == Enum_type_dungeon_generator::ROOM)))

	{
		// Porte Veticale
		if ((centre & Enum_type_dungeon_generator::DOOR) == Enum_type_dungeon_generator::DOOR)
		{
			return 11;
		}
		// Grille Veticale
		if ((centre & Enum_type_dungeon_generator::PORTC) == Enum_type_dungeon_generator::PORTC)
		{
			return 12;
		}
		// Arche Veticale
		if ((centre & Enum_type_dungeon_generator::ARCH) == Enum_type_dungeon_generator::ARCH)
		{
			return 13;
		}
		// Porte Veticale Lock
		if ((centre & Enum_type_dungeon_generator::LOCKED) == Enum_type_dungeon_generator::LOCKED)
		{
			return 14;
		}
		// Porte Veticale blocké Lock
		if ((centre & Enum_type_dungeon_generator::SECRET) == Enum_type_dungeon_generator::SECRET)
		{
			return 15;
		}
	}
	return 0;
	
}
raylib::Color Block::getBlockType(long long centre)
{
	raylib::Color returnColor{};
	returnColor = { 255,0,0,255 };
	if ((centre & Enum_type_dungeon_generator::NOTHING) == Enum_type_dungeon_generator::NOTHING)
	{
		//TileSet Vide
		returnColor = { 0,0,0 ,255 };
	}
	if ((centre & Enum_type_dungeon_generator::CORRIDOR) == Enum_type_dungeon_generator::CORRIDOR)
	{
		//TileSet Sol
		returnColor = { 255,0,0 ,255 };
	}
	if ((centre & Enum_type_dungeon_generator::ROOM) == Enum_type_dungeon_generator::ROOM)
	{
		//TileSet Sol
		returnColor = { 128,0,0 ,255 };
	}
	if ((centre & Enum_type_dungeon_generator::PERIMETER) == Enum_type_dungeon_generator::PERIMETER)
	{
		//TileSet Mur
		 returnColor = { 0,255,0,255 };


	}

	return returnColor;
}
int Block::getTilesetBlock(long long centre,long long haut, long long bas, long long gauche, long long droite)
{
	if (centre == Enum_type_dungeon_generator::NOTHING)
	{
		//TileSet Vide
		
		return vide(haut, bas, gauche, droite);
	}
	if (centre == Enum_type_dungeon_generator::CORRIDOR)
	{
		//TileSet Sol
		return sol(haut, bas, gauche, droite);
	}
	if (centre == Enum_type_dungeon_generator::PERIMETER)
	{
		//TileSet Mur
	
		return mur( haut, bas,  gauche, droite);
	}
	return sol(haut, bas, gauche, droite);
}
int Block::porte(long long haut, long long bas, long long gauche, long long droite)
{
	if (((haut & Enum_type_dungeon_generator::PERIMETER) != Enum_type_dungeon_generator::PERIMETER) &&
		((bas & Enum_type_dungeon_generator::PERIMETER) != Enum_type_dungeon_generator::PERIMETER))
	{
		return 234;
	}
	if (((gauche & Enum_type_dungeon_generator::PERIMETER) != Enum_type_dungeon_generator::PERIMETER) &&
		((droite & Enum_type_dungeon_generator::PERIMETER) != Enum_type_dungeon_generator::PERIMETER))
	{
		return 235;
	}


	return 0;
}
int Block::mur(long long haut, long long bas, long long gauche, long long droite)
{
	Randomer rand(0, 99);

	if (((haut & Enum_type_dungeon_generator::PERIMETER) != Enum_type_dungeon_generator::PERIMETER) &&
		((bas & Enum_type_dungeon_generator::PERIMETER) != Enum_type_dungeon_generator::PERIMETER))
	{

		if (((gauche & Enum_type_dungeon_generator::PERIMETER) == Enum_type_dungeon_generator::PERIMETER) &&
			((droite & Enum_type_dungeon_generator::PERIMETER) == Enum_type_dungeon_generator::PERIMETER))
		{
			
			// Mur horiz continue : 162[0-79] / 164(crack)[80-89] / 184(crack)[90-99]
			int choix_mur = rand();
			if (choix_mur < 80)
			{
				return 162;
			}
			if (choix_mur > 79 && choix_mur < 90)
			{
				return 164;
			}
			else
			{
				return 184;
			}
		}
		if (((gauche & Enum_type_dungeon_generator::PERIMETER) == Enum_type_dungeon_generator::PERIMETER) &&
			((droite & Enum_type_dungeon_generator::PERIMETER) != Enum_type_dungeon_generator::PERIMETER))
		{
			// Mur fin à droite avec porte
			if (((droite & Enum_type_dungeon_generator::DOOR) == Enum_type_dungeon_generator::DOOR) ||
				((droite & Enum_type_dungeon_generator::ARCH) == Enum_type_dungeon_generator::ARCH))
			{
				return 212;
			}
			// Mur fin à droite
			return 163;

		}
		if (((gauche & Enum_type_dungeon_generator::PERIMETER) != Enum_type_dungeon_generator::PERIMETER) &&
			((droite & Enum_type_dungeon_generator::PERIMETER) == Enum_type_dungeon_generator::PERIMETER))
		{
			// Mur fin à gauche avec porte
			if (((gauche & Enum_type_dungeon_generator::DOOR) == Enum_type_dungeon_generator::DOOR) ||
				((gauche & Enum_type_dungeon_generator::ARCH) == Enum_type_dungeon_generator::ARCH))
			{
				return 213;
			}
			// Mur fin à gauche
			return 161;

		}
		if (((gauche & Enum_type_dungeon_generator::PERIMETER) != Enum_type_dungeon_generator::PERIMETER) &&
			((droite & Enum_type_dungeon_generator::PERIMETER) != Enum_type_dungeon_generator::PERIMETER))
		{
			// Mur seul (type colonne)
			return 160;

		}
	}
	if (((haut & Enum_type_dungeon_generator::PERIMETER) == Enum_type_dungeon_generator::PERIMETER) &&
		((bas & Enum_type_dungeon_generator::PERIMETER) == Enum_type_dungeon_generator::PERIMETER))
	{

		if (((gauche & Enum_type_dungeon_generator::PERIMETER) == Enum_type_dungeon_generator::PERIMETER) &&
			((droite & Enum_type_dungeon_generator::PERIMETER) == Enum_type_dungeon_generator::PERIMETER))
		{
			// Mur en croix
			return 183;
		}
		if (((gauche & Enum_type_dungeon_generator::PERIMETER) == Enum_type_dungeon_generator::PERIMETER) &&
			((droite & Enum_type_dungeon_generator::PERIMETER) != Enum_type_dungeon_generator::PERIMETER))
		{
			// Mur en T vers la gauche
			return 221;

		}
		if (((gauche & Enum_type_dungeon_generator::PERIMETER) != Enum_type_dungeon_generator::PERIMETER) &&
			((droite & Enum_type_dungeon_generator::PERIMETER) == Enum_type_dungeon_generator::PERIMETER))
		{
			// Mur en T vers la droite
			return 223;

		}
		if (((gauche & Enum_type_dungeon_generator::PERIMETER) != Enum_type_dungeon_generator::PERIMETER) &&
			((droite & Enum_type_dungeon_generator::PERIMETER) != Enum_type_dungeon_generator::PERIMETER))
		{
			// Mur verti continue : 200[0-79] / 204(crack)[80-89] / 224(crack)[90-99]
			int choix_mur = rand();
			if (choix_mur < 80)
			{
				return 200;
			}
			if (choix_mur > 79 && choix_mur < 90)
			{
				return 204;
			}
			else
			{
				return 224;
			}

		}
	}
	if (((haut & Enum_type_dungeon_generator::PERIMETER) != Enum_type_dungeon_generator::PERIMETER) &&
		((bas & Enum_type_dungeon_generator::PERIMETER) == Enum_type_dungeon_generator::PERIMETER))
	{
		if (((gauche & Enum_type_dungeon_generator::PERIMETER) != Enum_type_dungeon_generator::PERIMETER) &&
			((droite & Enum_type_dungeon_generator::PERIMETER) == Enum_type_dungeon_generator::PERIMETER))
		{
			// Mur coin haut gauche
			return 181;

		}
		if (((gauche & Enum_type_dungeon_generator::PERIMETER) == Enum_type_dungeon_generator::PERIMETER) &&
			((droite & Enum_type_dungeon_generator::PERIMETER) == Enum_type_dungeon_generator::PERIMETER))
		{
			// Mur en T 
			return 222;

		}
		if (((gauche & Enum_type_dungeon_generator::PERIMETER) == Enum_type_dungeon_generator::PERIMETER) &&
			((droite & Enum_type_dungeon_generator::PERIMETER) != Enum_type_dungeon_generator::PERIMETER))
		{
			// Mur coin haut droite
			return 182;

		}
		if (((gauche & Enum_type_dungeon_generator::PERIMETER) != Enum_type_dungeon_generator::PERIMETER) &&
			((droite & Enum_type_dungeon_generator::PERIMETER) != Enum_type_dungeon_generator::PERIMETER))
		{
			// Mur fin haut
			return 180;

		}
	}
	if (((haut & Enum_type_dungeon_generator::PERIMETER) == Enum_type_dungeon_generator::PERIMETER) &&
		((bas & Enum_type_dungeon_generator::PERIMETER) != Enum_type_dungeon_generator::PERIMETER))
	{
		if (((gauche & Enum_type_dungeon_generator::PERIMETER) != Enum_type_dungeon_generator::PERIMETER) &&
			((droite & Enum_type_dungeon_generator::PERIMETER) == Enum_type_dungeon_generator::PERIMETER))
		{
			// Mur coin bas gauche
			return 201;

		}
		if (((gauche & Enum_type_dungeon_generator::PERIMETER) == Enum_type_dungeon_generator::PERIMETER) &&
			((droite & Enum_type_dungeon_generator::PERIMETER) == Enum_type_dungeon_generator::PERIMETER))
		{
			// Mur en T 
			return 203;

		}
		if (((gauche & Enum_type_dungeon_generator::PERIMETER) == Enum_type_dungeon_generator::PERIMETER) &&
			((droite & Enum_type_dungeon_generator::PERIMETER) != Enum_type_dungeon_generator::PERIMETER))
		{
			// Mur coin bas droite
			return 202;

		}
		if (((gauche & Enum_type_dungeon_generator::PERIMETER) != Enum_type_dungeon_generator::PERIMETER) &&
			((droite & Enum_type_dungeon_generator::PERIMETER) != Enum_type_dungeon_generator::PERIMETER))
		{
			// Mur fin bas
			return 220;

		}
	}
	
	return 0;
}



int Block::sol(long long haut, long long bas, long long gauche, long long droite)
{
	Randomer rand(0, 8);
	int choix_sol = rand();
	switch (choix_sol)
	{
		case 1:
			return 20;
			break;
		case 2:
			return 22;
			break;
		case 3:
			return 23;
			break;
	}
	

	return 21;
}
int Block::vide(long long haut, long long bas, long long gauche, long long droite)
{
	if ( (haut == Enum_type_dungeon_generator::NOTHING) &&
		(bas == Enum_type_dungeon_generator::NOTHING) )
	{

		if ((gauche == Enum_type_dungeon_generator::NOTHING) &&
			(droite == Enum_type_dungeon_generator::NOTHING))
		{
			return 3;
		}
		if ((gauche == Enum_type_dungeon_generator::NOTHING) &&
			(droite != Enum_type_dungeon_generator::NOTHING))
		{
			return 36;
		}
		if ((gauche != Enum_type_dungeon_generator::NOTHING) &&
			(droite == Enum_type_dungeon_generator::NOTHING))
		{
			return 34;
		}
		if ((gauche != Enum_type_dungeon_generator::NOTHING) &&
			(droite != Enum_type_dungeon_generator::NOTHING))
		{
			return 39;
		}
	}
	if ((haut == Enum_type_dungeon_generator::NOTHING) && 
		(bas != Enum_type_dungeon_generator::NOTHING))
	{
		if ((gauche == Enum_type_dungeon_generator::NOTHING) &&
			(droite == Enum_type_dungeon_generator::NOTHING))
		{
			return 55;
		}
		if ((gauche != Enum_type_dungeon_generator::NOTHING) &&
			(droite != Enum_type_dungeon_generator::NOTHING))
		{
			return 79;
		}
		if ((gauche == Enum_type_dungeon_generator::NOTHING) &&
			(droite != Enum_type_dungeon_generator::NOTHING))
		{
			return 56;
		}
		if ((gauche != Enum_type_dungeon_generator::NOTHING) &&
			(droite == Enum_type_dungeon_generator::NOTHING))
		{
			return 54;
		}
	}
	if ((haut != Enum_type_dungeon_generator::NOTHING) &&
		(bas != Enum_type_dungeon_generator::NOTHING))
	{
		if ((gauche == Enum_type_dungeon_generator::NOTHING) &&
			(droite == Enum_type_dungeon_generator::NOTHING))
		{
			return 58;
		}
		if ((gauche != Enum_type_dungeon_generator::NOTHING) &&
			(droite != Enum_type_dungeon_generator::NOTHING))
		{
			return 78;
		}
		if ((gauche == Enum_type_dungeon_generator::NOTHING) &&
			(droite != Enum_type_dungeon_generator::NOTHING))
		{
			return 59;
		}
		if ((gauche != Enum_type_dungeon_generator::NOTHING) &&
			(droite == Enum_type_dungeon_generator::NOTHING))
		{
			return 57;
		}
	}
	if ((haut != Enum_type_dungeon_generator::NOTHING) &&
		(bas == Enum_type_dungeon_generator::NOTHING))
	{
		if ((gauche == Enum_type_dungeon_generator::NOTHING) &&
			(droite == Enum_type_dungeon_generator::NOTHING))
		{
			return 15;
		}
		if ((gauche != Enum_type_dungeon_generator::NOTHING) &&
			(droite != Enum_type_dungeon_generator::NOTHING))
		{
			return 77;
		}
		if ((gauche == Enum_type_dungeon_generator::NOTHING) &&
			(droite != Enum_type_dungeon_generator::NOTHING))
		{
			return 16;
		}
		if ((gauche != Enum_type_dungeon_generator::NOTHING) &&
			(droite == Enum_type_dungeon_generator::NOTHING))
		{
			return 14;
		}
	}
	return 3;
}
