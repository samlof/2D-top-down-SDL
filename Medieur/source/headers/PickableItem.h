#pragma once

enum class ItemType {
	FOOD,
	TOOL,
	JOY
};

class Character;
class Tile;

class PickableItem {
public:
	PickableItem(PickableItem* pPrototype, const int pAmount)
		: mId(pPrototype->mId), mMaxAmount(pPrototype->mMaxAmount), mAmount(pAmount),
		mCharacter(nullptr), mTile(nullptr) {}
	PickableItem(PickableItem* pPrototype) : PickableItem(pPrototype, 0) {}

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
	void erase();

	Character* mCharacter;
	Tile* mTile;
private:
	const int mId;
	const int mMaxAmount;
	int mAmount;

	// Prototype
	PickableItem(const int pId, const int pMaxAmount)
		: mId(pId), mMaxAmount(pMaxAmount), mAmount(0) {}
public:
	static PickableItem* createPrototype(const int pId, const int pMaxAmount) {
		return new PickableItem(pId, pMaxAmount);
	}
};