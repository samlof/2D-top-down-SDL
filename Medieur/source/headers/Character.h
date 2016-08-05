#pragma once

#include <stack>

#include "Point.h"
#include "CountdownCounter.h"

class Job;
class Tile;
class World;

class Character {
public:
	Character(World* pWorld, Tile* pTile, int pX, int pY);

	void setPathTo(Tile* pGoalTile);
	void getNextTile();

	void setJob(Job* pJob) { mCurrentJob = pJob; }
	void clearJob() { mCurrentJob = nullptr; }

	void update();
private:
	int mX, mY;
	bool mMoving;
	CountdownCounter mMoveCounter;

	World* mWorld;
	Tile* mTile;
	Tile* mNextTile;
	Job* mCurrentJob;
	std::stack<Tile*> mPathTiles;

	void moveTowardsNextTile();
};