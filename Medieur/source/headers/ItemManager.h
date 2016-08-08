#pragma once

#include <memory>
#include <unordered_map>

class PickableItem;

class ItemManager {
public:
	ItemManager();
	~ItemManager();

	// Assigns to ItemMap. Delete thru itemmap or item.erase
	PickableItem* createPickableItem(int pId, const int pAmount);
	// Doesn't assign to ItemMap. Deletion is on caller to handle
	static PickableItem* createLocalPickableItem(int pId, const int pAmount);
	void deleteItem(PickableItem* pItem);
private:

	using ItemMap = std::unordered_multimap<int, std::unique_ptr<PickableItem> >;
	ItemMap mItems;
};