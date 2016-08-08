#include "Tile.h"

#include "GroundEntity.h"
#include "PickableItem.h"
#include "World.h"
#include "IGroundEntityModule.h"
#include "ItemManager.h"

Tile::Tile(Tile* pPrototype, World* pWorld, int pX, int pY)
	:
	mTileType(pPrototype->mTileType),
	mX(pX), mY(pY),
	mMovementCost(1.0f),
	mCharacterStandingOn(false),
	mWorld(pWorld), mId(pPrototype->mId)
{
}
Tile::~Tile() = default;

#pragma region Gets and sets
bool Tile::isWalkable() const
{
	bool walkable = mMovementCost > 0;
	if (hasGroundEntity()) {
		walkable = mGroundEntity->isWalkable();
	}
	return walkable;
}
void Tile::addItem(PickableItem * pItem)
{
	// Create a 'global' item
	PickableItem* newItem = mWorld->getItemManager()->createPickableItem(pItem->getId(), pItem->getAmount());
	// TODO: check if can add to existing one, or can't at all
	mItems.insert(ItemMap::value_type(pItem->getId(), newItem));
}
void Tile::clearItem(PickableItem * pItem)
{
	auto iters = mItems.equal_range(pItem->getId());
	for (auto it = iters.first; it != iters.second; it++) {
		if (it->second == pItem) {
			mItems.erase(it);
			break;
		}
	}
}

PickableItem * Tile::getItemOfId(const int pId)
{
	auto iters = mItems.equal_range(pId);
	for (auto it = iters.first; it != iters.second; it++) {
		return it->second;
	}
	return nullptr;
}
int Tile::getItemId()
{
	for (auto it : mItems) {
		return it.first;
	}
	throw "No items!";
}
#pragma endregion

