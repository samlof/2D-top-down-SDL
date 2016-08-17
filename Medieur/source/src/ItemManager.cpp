#include "ItemManager.h"


#include "Tile.h"
#include "Character.h"
#include "Prototypes.h"
#include "InventoryItem.h"

ItemManager::ItemManager()
{
}

ItemManager::~ItemManager() = default;

InventoryItem* ItemManager::createPickableItem(int pId, const int pAmount)
{
	InventoryItem* pPrototype = Prototypes::getPickableItemPrototypeById(pId);
	InventoryItem* newItem = new InventoryItem(pPrototype, this, pAmount);
	mItems.insert(ItemMap::value_type(newItem->getId(), std::unique_ptr<InventoryItem>(newItem)));
	return newItem;
}

InventoryItem * ItemManager::createLocalPickableItem(int pId, const int pAmount)
{
	InventoryItem* pPrototype = Prototypes::getPickableItemPrototypeById(pId);
	InventoryItem* newItem = new InventoryItem(pPrototype, nullptr, pAmount);
	return newItem;
}



void ItemManager::deleteItem(InventoryItem * pItem)
{
	auto iters = mItems.equal_range(pItem->getId());
	for (auto it = iters.first; it != iters.second; it++) {
		if (it->second.get() == pItem) {
			mItems.erase(it);
			break;
		}
	}
}

void ItemManager::moveToStockpile(InventoryItem * pItem)
{
	mStockpiledItems.insert(ItemMap::value_type(
		pItem->getId(), pItem
	));

	auto iters = mItems.equal_range(pItem->getId());
	for (auto it = iters.first; it != iters.second; it++) {
		if (it->second.get() == pItem) {
			it->second.release();
			mItems.erase(it);
			break;
		}
	}
}