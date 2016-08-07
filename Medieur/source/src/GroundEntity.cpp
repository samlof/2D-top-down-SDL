#include "GroundEntity.h"

#include "Tile.h"
#include "IGroundEntityModule.h"

GroundEntity::GroundEntity(GroundEntity * pPrototype, Tile * pTilePtr)
: mId(pPrototype->mId), mMovementCost(pPrototype->mMovementCost), mTilePtr(pTilePtr),
mModule(nullptr) {}

GroundEntity::~GroundEntity() = default;

void GroundEntity::erase()
{
	mTilePtr->clearGroundEntity();
}



GroundEntity::GroundEntity(const int pId, const float pMovCost)
	: mId(pId), mMovementCost(pMovCost), mTilePtr(nullptr), mModule(nullptr) {}