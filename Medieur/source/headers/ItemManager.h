#pragma once

#include <memory>
#include <unordered_map>

class InventoryItem;

class ItemManager {
public:
	ItemManager();
	~ItemManager();

	// Assigns to ItemMap. Delete thru itemmap or item.erase
	InventoryItem* createPickableItem(int pId, const int pAmount);
	// Doesn't assign to ItemMap. Deletion is on caller to handle
	static InventoryItem* createLocalPickableItem(int pId, const int pAmount);
	// Just erases from global map and deletes pointer. Clear other pointers
	void deleteItem(InventoryItem* pItem);
	void moveToStockpile(InventoryItem* pItem);
	bool hasItemOfId(const int pId) { return mItems.count(pId) > 0 || mStockpiledItems.count(pId) > 0; }
	bool hasItemOfIdOutsideStockpile(const int pId) { return mItems.count(pId) > 0; }

private:

	using ItemMap = std::unordered_multimap<int, std::unique_ptr<InventoryItem> >;
	ItemMap mItems;
	ItemMap mStockpiledItems;
};