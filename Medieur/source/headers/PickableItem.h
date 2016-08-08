#pragma once

enum class ItemType {
	FOOD,
	TOOL,
	JOY
};

class ItemManager;

class PickableItem {
public:
	PickableItem(PickableItem* pPrototype, ItemManager * pItemManager, const int pAmount)
		: mId(pPrototype->mId), mMaxAmount(pPrototype->mMaxAmount), mAmount(pAmount),
		mItemManager(pItemManager) {}

	void takeAmountFrom(PickableItem* pItem, int pAmount);

	// Helper methods
	void AddAmountTo(PickableItem* pItem, int pAmount) { pItem->takeAmountFrom(this, pAmount); }
	void addTo(PickableItem* pItem) { AddAmountTo(pItem, mAmount); }
	void takeFrom(PickableItem* pItem) { takeAmountFrom(pItem, pItem->mAmount); }

	bool isFull() const { return mAmount == mMaxAmount; }
	bool isEmpty() const { return mAmount == 0; }
	bool isOfType(const int pId) const { return mId == pId; }
	bool isSameType(const PickableItem* pItem) const { return pItem->mId == mId; }

	int getId() const { return mId; }
	int getAmount() const { return mAmount; }
	int getMaxAmount() const { return mMaxAmount; }

	void changeMax(const int pMaxAmount) { mMaxAmount = pMaxAmount; }

	void erase();

private:
	const int mId;
	int mMaxAmount;
	int mAmount;
	ItemManager * mItemManager;

	// Prototype
	PickableItem(const int pId, const int pMaxAmount)
		: mId(pId), mMaxAmount(pMaxAmount), mAmount(0), mItemManager(nullptr) {}
public:
	static PickableItem* createPrototype(const int pId, const int pMaxAmount) {
		return new PickableItem(pId, pMaxAmount);
	}
};