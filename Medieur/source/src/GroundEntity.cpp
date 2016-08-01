#include "GroundEntity.h"

#include "Tile.h"
void GroundEntity::erase()
{
	mTilePtr->clearGroundEntity();
}
