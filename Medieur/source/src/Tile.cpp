#include "Tile.h"

#include "GroundEntity.h"
#include "InventoryItem.h"
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

void Tile::addItem(InventoryItem * pItem)
{
	const int id = pItem->getId();

	// Find if there is an existing inventoryitem
	auto iters = mItems.equal_range(id);
	for (auto it = iters.first; it != iters.second; it++) {
		it->second->takeFrom(pItem);
		if (pItem->isEmpty()) return;
	}
	if (pItem->isEmpty() == false) {
		// Create a new 'global' item
		InventoryItem* newItem = mWorld->getItemManager()->createPickableItem(id, 0);
		newItem->takeFrom(pItem);
		mItems.insert(ItemMap::value_type(id, newItem));
	}
}

void Tile::fillItem(InventoryItem * pItem)
{
	auto iters = mItems.equal_range(pItem->getId());
	for (auto it = iters.first; it != iters.second;) {
		printf("Amount in hand before %i\n", pItem->getAmount());
		pItem->takeFrom(it->second);
		printf("Amount in hand after %i\n", pItem->getAmount());
		printf("Amount in tile left: %i\n", it->second->getAmount());
		if (it->second->isEmpty()) {
			getWorld()->getItemManager()->deleteItem(it->second);
			it = mItems.erase(it);
		}
		else {
			it++;
		}
		if (pItem->isFull()) return;
	}
}

void Tile::clearItem(InventoryItem * pItem)
{
	auto iters = mItems.equal_range(pItem->getId());
	for (auto it = iters.first; it != iters.second; it++) {
		if (it->second == pItem) {
			getWorld()->getItemManager()->deleteItem(it->second);
			mItems.erase(it);
			return;
		}
	}
}

int Tile::getItemCountOfId(const int pId) const
{
	int count = 0;
	auto iters = mItems.equal_range(pId);
	for (auto it = iters.first; it != iters.second; it++) {
		count += it->second->getAmount();
		count++;
	}
	return count;
}

int Tile::getItemMaxCount(const int pId) const
{
	int count = 0;
	auto iters = mItems.equal_range(pId);
	for (auto it = iters.first; it != iters.second; it++) {
		count += it->second->getMaxAmount();
		count++;
	}
	return count;
}

bool Tile::hasItemId(const int pId) const
{
	auto iters = mItems.equal_range(pId);
	for (auto it = iters.first; it != iters.second; it++) {
		return true;
	}
	return false;
}
int Tile::getItemId()
{
	for (auto it : mItems) {
		return it.first;
	}
	throw "No items!";
}
#pragma endregion

