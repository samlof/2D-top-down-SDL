#include "PickableItem.h"

#include <stdexcept>

#include "Tile.h"
#include "World.h"
#include "Character.h"

void PickableItem::takeAmountFrom(PickableItem * pItem, int pAmount)
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

void PickableItem::erase()
{
	if (mTile != nullptr) {
		mTile->getWorld()->deleteItem(this);
	}
	else if (mCharacter != nullptr) {
		mCharacter->getWorld()->deleteItem(this);
	}
	else {
		throw "Item isn't owned by anything!";
	}
}
