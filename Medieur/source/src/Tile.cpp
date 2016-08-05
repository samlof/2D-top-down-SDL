#include "Tile.h"

#include "GroundEntity.h"

Tile::Tile(World* pWorld, TileType pTileType, int pX, int pY)
	:
	mTileType(pTileType),
	mX(pX), mY(pY),
	mMovementCost(1.0f),
	mCharacterStandingOn(false),
	mWorld(pWorld)
{
}

#pragma region Gets and sets
void Tile::setTileType(TileType pTileType)
{
	mTileType = pTileType;
}
std::shared_ptr<GroundEntity> Tile::getGroundEntity()
{
	return mGroundEntity;
}
bool Tile::isWalkable() const
{
	bool walkable = mMovementCost > 0;
	if (hasGroundEntity()) {
		walkable = mGroundEntity->isWalkable();
	}
	return walkable;
}
#pragma endregion

