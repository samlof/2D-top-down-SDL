#pragma once

#include <stack>

#include "Point.h"
#include "CountdownCounter.h"

class Job;
class Tile;
class World;

class Character {
public:
	Character(Character* pPrototype, World* pWorld, Tile* pTile, int pX, int pY);
	// For prototype
	Character(const int pId);

	void setPathTo(Tile* pGoalTile);
	void getNextTile();

	void setJob(Job* pJob) { mCurrentJob = pJob; }
	void clearJob() { mCurrentJob = nullptr; }

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

	void moveTowardsNextTile();
	void getJob();
};