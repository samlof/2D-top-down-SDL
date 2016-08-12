#pragma once

#include <memory>
#include <unordered_map>

#include "Point.h"

class GroundEntity;
class InventoryItem;
class Character;
class World;

enum class TileType {
	GRASS,
	EMPTY
};

class Tile
{
public:
	Tile(Tile* pPrototype, World* pWorld, int pX, int pY);
	~Tile();

	TileType getTileType() const { return mTileType; }

	//Ground entity functions
	std::shared_ptr<GroundEntity> getGroundEntity() { return mGroundEntity; }
	bool hasGroundEntity() const { return static_cast<bool>(mGroundEntity); }
	void setGroundEntity(std::shared_ptr<GroundEntity> pGroundEntity) { mGroundEntity = pGroundEntity; }
	void clearGroundEntity() { mGroundEntity.reset(); }

	// Character functions
	Character* getCharacter() { return mCharacter; }
	bool isReservableForCharacter() { return mCharacter == nullptr; }
	void reserveFor(Character* pCharacter) { if(isReservableForCharacter()) mCharacter = pCharacter; }
	void moveTo() { if(mCharacter != nullptr) mCharacterStandingOn = true; }
	bool isCharacterOn() const { return mCharacterStandingOn; }
	void clearCharater() { mCharacter = nullptr; mCharacterStandingOn = false; }

	// Pickable Item stuff
	void addItem(InventoryItem* pItem);
	void clearItem(InventoryItem* pItem);
	InventoryItem * getItemOfId(const int pId);
	bool hasItems() { return mItems.size() > 0; }
	int getItemId();

	// Tile gets and sets
	bool isWalkable() const;
	int getX() const { return mX; }
	int getY() const { return mY; }
	World* getWorld() { return mWorld; }
	Point getXY() const { return Point{ mX, mY }; }
	int getId() const { return mId; }


private:
	World* mWorld;
	const int mId;
	const int mX, mY;
	TileType mTileType;
	std::shared_ptr<GroundEntity> mGroundEntity;
	Character* mCharacter;
	bool mCharacterStandingOn;
	float mMovementCost;

	using ItemMap = std::unordered_multimap<int, InventoryItem*>;
	ItemMap mItems;


	// For prototype
	Tile(const int pId, TileType pTileType) :
		mId(pId), mTileType(pTileType), mX(-1), mY(-1) {}
public:
	static Tile* createPrototype(const int pId, const TileType pTileType) {
		return new Tile(pId, pTileType);
	}
};

