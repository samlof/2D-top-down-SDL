#pragma once

#include <stack>

#include "Point.h"
#include "CountdownCounter.h"

class Job;
class Tile;
class World;
class PickableItem;

class Character {
public:
	Character(Character* pPrototype, World* pWorld, Tile* pTile, int pX, int pY);

	void setPathTo(Tile* pGoalTile);

	void setJob(Job* pJob) { mCurrentJob = pJob; }
	void clearJob() { mCurrentJob = nullptr; }

	void addItem(PickableItem* pItem);
	void clearItem();

	World* getWorld() { return mWorld; }
	int getId() const { return mId; }
	void update();
private:
	const int mId;
	int mX, mY;
	CountdownCounter mMoveCounter;
	CountdownCounter mJobInterval;

	World* mWorld;
	Tile* mTile;
	Tile* mNextTile;
	Job* mCurrentJob;
	std::stack<Tile*> mPathTiles;
	PickableItem* mItem;

	void getNextTile();
	void moveTowardsNextTile();
	void getJob();


	// For prototype
	Character(const int pId);
public:
	static Character* createPrototype(const int pId) {
		return new Character(pId);
	}
};