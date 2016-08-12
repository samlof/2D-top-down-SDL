#include "InventoryItem.h"

#include <stdexcept>

#include "Tile.h"
#include "World.h"
#include "Character.h"
#include "ItemManager.h"

void InventoryItem::takeAmountFrom(InventoryItem * pItem, int pAmount)
{
	if (isSameType(pItem) == false) {
		throw std::invalid_argument("Trying to take items from different type item!");
		return;
	}

	if (pAmount > pItem->mAmount) {
		// Can't take that many
		pAmount = pItem->mAmount;
	}

	// Check if can add all of it
	if (pAmount > (mMaxAmount - mAmount)) {
		// Add less
		pAmount = mMaxAmount - mAmount;
	}

	mAmount += pAmount;
	pItem->mAmount -= pAmount;
}


void InventoryItem::erase()
{
	if (mItemManager == nullptr) throw "Item is local!";
	mItemManager->deleteItem(this);
}
