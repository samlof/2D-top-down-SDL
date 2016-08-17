#pragma once

#include <unordered_map>
#include <memory>

class Tile;
class IGroundEntityModule;

class GroundEntity {
public:
	// Create from prototype
	GroundEntity(GroundEntity* pPrototype, Tile* pTilePtr);
	~GroundEntity();

	int getId() const { return mId; }
	float getMovementCost() const { return mMovementCost; }
	Tile* getTile() const { return mTilePtr; }
	bool isWalkable() const { return mMovementCost > 0; }

	void erase();

	std::unique_ptr<IGroundEntityModule> mModule;
private:
	friend class IGroundEntityModule;
	int mId;
	Tile* const mTilePtr;
	float mMovementCost;

	// Only for making prototypes
	GroundEntity(const int pId, const float pMovCost);
public:
	static GroundEntity* createPrototype(const int pId, const float pMovCost) {
		return new GroundEntity(pId, pMovCost);
	}
};