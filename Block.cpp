#include "Block.h"

Block::Block()
{
}

Block::~Block()
{
}

int Block::getTilesetBlock(int couche,long long centre,long long haut, long long bas, long long gauche, long long droite)
{
	if (centre == Enum_type_dungeon_generator::NOTHING)
	{
		//TileSet mur
		
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
	if (couche == 0)
	{
		return sol(haut, bas, gauche, droite);
	}
	else
	{
		if ((centre & Enum_type_dungeon_generator::DOOR) == Enum_type_dungeon_generator::DOOR)
		{
			//TilSet Porte
			return porte(haut, bas, gauche, droite);
		}
		if ((centre & Enum_type_dungeon_generator::ARCH) == Enum_type_dungeon_generator::ARCH)
		{
			//TilSet Porte
			return 234;
		}
	}

	return 0;

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
			return 283;
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
	
	
	return 0;
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
		if ( (gauche == Enum_type_dungeon_generator::NOTHING) &&
			((droite & Enum_type_dungeon_generator::CORRIDOR) == Enum_type_dungeon_generator::CORRIDOR))
		{
			return 36;
		}
		if (((gauche & Enum_type_dungeon_generator::CORRIDOR) == Enum_type_dungeon_generator::CORRIDOR) &&
			(droite == Enum_type_dungeon_generator::NOTHING))
		{
			return 34;
		}
		if (((gauche & Enum_type_dungeon_generator::CORRIDOR) == Enum_type_dungeon_generator::CORRIDOR) &&
			((droite & Enum_type_dungeon_generator::CORRIDOR) == Enum_type_dungeon_generator::CORRIDOR))
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
			return 0;
		}
		if ((gauche != Enum_type_dungeon_generator::NOTHING) &&
			(droite != Enum_type_dungeon_generator::NOTHING))
		{
			return 78;
		}
		if ((gauche == Enum_type_dungeon_generator::NOTHING) &&
			(droite != Enum_type_dungeon_generator::NOTHING))
		{
			return 0;
		}
		if ((gauche != Enum_type_dungeon_generator::NOTHING) &&
			(droite == Enum_type_dungeon_generator::NOTHING))
		{
			return 0;
		}
	}
	return 3;
}
