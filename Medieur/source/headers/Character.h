#pragma once

#include <stack>
#include <memory>

#include "CountdownCounter.h"

class Job;
class Tile;
class World;
class InventoryItem;

class Character {
public:
	Character(Character* pPrototype, World* pWorld, Tile* pTile, int pX, int pY);
	~Character();


	void setPathTo(Tile* pGoalTile);
	void cancelPath();

	void setJob(Job* pJob) { mCurrentJob = pJob; }
	// Sets current job to nullptr. Should be called from job.clearCharacter()
	void clearJob() { mCurrentJob = nullptr; }

	void addItem(InventoryItem* pItem);
	InventoryItem* getItem() { return mItem.get(); }
	void clearItem();

	World* getWorld() { return mWorld; }
	Tile* getTile() { return mTile; }
	int getId() const { return mId; }
	void update();
private:
	const int mId;
	int mX, mY;
	CountdownCounter mMoveCounter;
	CountdownCounter mJobInterval;

	World* mWorld;
	Tile* mTile, *mNextTile, *mGoalTile;
	Job* mCurrentJob;
	std::stack<Tile*> mPathTiles;
	std::unique_ptr<InventoryItem> mItem;

	void getNextTile();
	void moveTowardsNextTile();
	void getJob();
	void doJob();

	// For prototype
	Character(const int pId);
public:
	static Character* createPrototype(const int pId) {
		return new Character(pId);
	}
};