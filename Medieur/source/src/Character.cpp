#include "Character.h"

#include "PathFinder.h"
#include "Tile.h"

namespace {
	const int kWalkSpeed = 100; // 100 frames for 1 tile
}
Character::Character(World * pWorld, Tile * pTile, int pX, int pY)
	:
	mWorld(pWorld), mTile(pTile), mX(pX), mY(pY), mMoveCounter(kWalkSpeed)
{
}

void Character::setPathTo(Tile * pGoalTile)
{
	mPathTiles = PathFinder::FindPath(mTile, pGoalTile);
	getNextTile();
}

void Character::update()
{
	if (mNextTile == nullptr) {
		return;
	}
	else if (mTile != mNextTile) {
		moveTowardsNextTile();
	}
}

void Character::getNextTile()
{
	if (mPathTiles.size() == 0) mNextTile = mTile;
	else {
		mNextTile = mPathTiles.top();
		mPathTiles.pop();
	}
}

void Character::moveTowardsNextTile()
{
	if (mNextTile->getCharacter() == mTile->getCharacter()) {
	}
	else if (mNextTile->isReservableForCharacter()) {
		mNextTile->reserveFor(mTile->getCharacter());
	}
	else return; // If reserved by someone else

	if (mMoveCounter.expired()) {
		// Update tiles
		mTile->clearCharater();
		mNextTile->moveTo();
		mTile = mNextTile;
		getNextTile();

		// Update character
		mX = mTile->getX();
		mY = mTile->getY();
		mMoveCounter.reset();
	}
	else {
		mMoveCounter.step();
	}
}
