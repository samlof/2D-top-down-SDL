#pragma once

#include <stack>

#include "Point.h"
#include "CountdownCounter.h"

class Tile;
class World;

class Character {
public:
	Character(World* pWorld, Tile* pTile, int pX, int pY);
	void setPathTo(Tile* pGoalTile);
	void update();

	void getNextTile();
private:
	int mX, mY;
	bool mMoving;
	CountdownCounter mMoveCounter;

	World* mWorld;
	Tile* mTile;
	Tile* mNextTile;
	std::stack<Tile*> mPathTiles;

	void moveTowardsNextTile();
};