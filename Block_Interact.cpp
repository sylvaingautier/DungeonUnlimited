#include "Block_Interact.h"

bool Block_Interact::operator==(const Block_Interact& b)
{
	// TODO: ins�rer une instruction return ici
	if ((b.x == x) && (b.y == y))
	{
		return true;
	}
	return false;
}
