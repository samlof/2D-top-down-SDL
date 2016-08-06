#include "Character.h"

#include "PathFinder.h"
#include "Tile.h"
#include "World.h"
#include "Job.h"
#include "GroundEntity.h"
#include "PickableItem.h"
#include "JobManager.h"

namespace {
	const int kWalkSpeed = 100; // 100 frames for 1 tile
	const int kJobInterval = 100;
}

Character::Character(Character* pPrototype, World* pWorld, Tile* pTile, int pX, int pY)
	:
	mWorld(pWorld), mTile(pTile), mX(pX), mY(pY),
	mMoveCounter(kWalkSpeed), mJobInterval(kJobInterval), mId(pPrototype->mId),
	mNextTile(nullptr), mCurrentJob(nullptr), mItem(nullptr), mGoalTile(nullptr)
{
}

Character::Character(const int pId)
	:
	mMoveCounter(kWalkSpeed), mJobInterval(kJobInterval), mId(pId)
{
}

void Character::setPathTo(Tile * pGoalTile)
{
	mPathTiles = PathFinder::FindPath(mTile, pGoalTile);
	getNextTile();
}

void Character::cancelPath()
{
	while (!mPathTiles.empty()) {
		mPathTiles.pop();
	}
}

void Character::addItem(PickableItem * pItem)
{
	if (mItem != nullptr) {
		mItem->takeFrom(pItem);
	}
	else {
		pItem->mTile = nullptr;
		pItem->mCharacter = this;
		mItem = pItem;
	}
}

void Character::clearItem()
{
	mItem->mCharacter = nullptr;
	mItem = nullptr;
}

void Character::update()
{
	// Try to get a new job if doesn't have one
	if (mCurrentJob == nullptr) {
		mJobInterval.step();

		if (mJobInterval.expired()) {
			getJob();
		}
	}
	else {
		if (mNextTile == nullptr) {
			mCurrentJob->getFunc()(this);
			mWorld->getJobManager()->deleteJob(mCurrentJob);
			mCurrentJob = nullptr;
			return;
		}
	}
	moveTowardsNextTile();
}

void Character::getNextTile()
{
	if (mPathTiles.size() == 0) mNextTile = nullptr;
	else {
		mNextTile = mPathTiles.top();
		mPathTiles.pop();
	}
}

void Character::moveTowardsNextTile()
{
	if (mNextTile == nullptr) return;
	// FIXME: make nicer
	if (mNextTile->getCharacter() == mTile->getCharacter()) {
	}
	else if (mNextTile->isReservableForCharacter()) {
		mNextTile->reserveFor(mTile->getCharacter());
	}
	else return; // If reserved by someone else

	if (mMoveCounter.expired()) {
		// At next tile, update tiles
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
		// Move towards next tile
		mMoveCounter.step();
	}
}

void Character::getJob()
{
	if (mWorld->getJobManager()->hasJobs()) {
		mCurrentJob = mWorld->getJobManager()->getJob();
		mCurrentJob->reserve(this);
		setPathTo(mCurrentJob->getTile());
		mJobInterval.reset();
	}
}
