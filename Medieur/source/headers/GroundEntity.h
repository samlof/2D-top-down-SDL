#pragma once

#include <unordered_map>
#include <string>
#include <memory>

#include "IGroundEntityModule.h"
class Tile;

class GroundEntity {
public:
	// Create from prototype
	GroundEntity(GroundEntity* pPrototype, Tile* pTilePtr)
		: mId(pPrototype->mId), mMovementCost(pPrototype->mMovementCost), mTilePtr(pTilePtr) {}
	// Only for making prototypes
	GroundEntity(int pId, float pMovCost)
		: mId(pId), mMovementCost(pMovCost), mTilePtr(nullptr) {}

	int getId() const { return mId; }
	float getMovementCost() const { return mMovementCost; }
	Tile* getTile() const { return mTilePtr; }
	bool isWalkable() const { return mMovementCost > 0; }

	void erase();

	std::unique_ptr<IGroundEntityModule> mModule;
private:
	int mId;
	Tile* const mTilePtr;
	float mMovementCost;
};