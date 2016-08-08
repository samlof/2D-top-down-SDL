#include "ItemManager.h"


#include "Tile.h"
#include "Character.h"
#include "Prototypes.h"
#include "PickableItem.h"

ItemManager::ItemManager()
{
}

ItemManager::~ItemManager() = default;

PickableItem* ItemManager::createPickableItem(int pId, const int pAmount)
{
	PickableItem* pPrototype = Prototypes::getPickableItemPrototypeById(pId);
	PickableItem* newItem = new PickableItem(pPrototype, this, pAmount);
	mItems.insert(ItemMap::value_type(newItem->getId(), std::unique_ptr<PickableItem>(newItem)));
	return newItem;
}

PickableItem * ItemManager::createLocalPickableItem(int pId, const int pAmount)
{
	PickableItem* pPrototype = Prototypes::getPickableItemPrototypeById(pId);
	PickableItem* newItem = new PickableItem(pPrototype, nullptr, pAmount);
	return newItem;
}


void ItemManager::deleteItem(PickableItem * pItem)
{
	auto iters = mItems.equal_range(pItem->getId());
	for (auto it = iters.first; it != iters.second; it++) {
		if (it->second.get() == pItem) {
			mItems.erase(it);
			break;
		}
	}
}