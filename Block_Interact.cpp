#include "Block_Interact.h"

bool Block_Interact::operator==(const Block_Interact& b)
{
	// TODO: insérer une instruction return ici
	if ((b.x == x) && (b.y == y))
	{
		return true;
	}
	return false;
}

const Block_Interact& Block_Interact::operator=(const Block_Interact& src)
{
	// TODO: insérer une instruction return ici

	Box= src.Box;
	Type = src.Type;
	Etat = src.Etat;
	x = src.x;
	y = src.y;
	return *this;
}
