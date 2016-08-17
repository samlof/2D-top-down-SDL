#include "Character.h"

#include "Tile.h"
#include "World.h"
#include "Job.h"
#include "PathFinder.h"
#include "JobManager.h"
#include "ItemManager.h"
#include "InventoryItem.h"

namespace {
	const int kWalkSpeed = 50; // 50 frames for 1 tile
	const int kJobInterval = 100;
}

Character::Character(Character* pPrototype, World* pWorld, Tile* pTile, int pX, int pY)
	:
	mWorld(pWorld), mTile(pTile), mX(pX), mY(pY),
	mMoveCounter(kWalkSpeed), mJobInterval(kJobInterval), mId(pPrototype->mId),
	mNextTile(nullptr), mCurrentJob(nullptr), mItem(nullptr), mGoalTile(nullptr)
{
}

Character::~Character() {
	clearItem();
}

Character::Character(const int pId)
	:
	mMoveCounter(kWalkSpeed), mJobInterval(kJobInterval), mId(pId)
{
}

void Character::setPathTo(Tile * pGoalTile)
{
	mGoalTile = pGoalTile;
	getNextTile();
}

void Character::cancelPath()
{
	while (!mPathTiles.empty()) {
		mPathTiles.pop();
	}
}

void Character::addItem(InventoryItem * pItem)
{
	if (mItem != nullptr) {
		if (mItem->isSameType(pItem)) {
			mItem->takeFrom(pItem);
		}
	}
	else {
		mItem.reset(ItemManager::createLocalPickableItem(pItem->getId(), 0));
		mItem->takeFrom(pItem);
	}
}


void Character::clearItem()
{
	if (mItem != nullptr) {
		mItem.reset(nullptr);
	}
}

void Character::update()
{
	// Try to get a new job if doesn't have one
	if (mCurrentJob == nullptr) {
		mJobInterval.step();

		if (mJobInterval.expired()) {
			getJob();
			mJobInterval.reset();
		}
	}
	else {
		// Does job have all requirements
		if (mCurrentJob->hasAllMaterials()) {
			if (mTile == mCurrentJob->getTile()) {
				doJob();
				mGoalTile = nullptr;
			}
			else if (mNextTile == nullptr) {
				mGoalTile = mCurrentJob->getTile();
				mPathTiles = PathFinder::FindPath(mTile, mGoalTile);
				getNextTile();
			}
		}
		else if (mItem == nullptr) {
			// mItem is empty, so find items required
			if (mTile == mGoalTile) {
				InventoryItem* req = mCurrentJob->getRequirement();
				mItem.reset(ItemManager::createLocalPickableItem(req->getId(), 0));
				mItem->changeMax(req->getToMaxAmount());
				mGoalTile->fillItem(mItem.get());
				mGoalTile = nullptr;
			}
			else if (mNextTile == nullptr) {
				// Get requirements
				InventoryItem* req = mCurrentJob->getRequirement();
				if (mWorld->getItemManager()->hasItemOfId(req->getId()) == false) {
					// No items of req type exist. Cancel reservation
					mCurrentJob->cancelReserve();
					mCurrentJob = nullptr;
					return;
				}
				mPathTiles = PathFinder::FindPathForInventoryWith(mTile, req, false);
				if (mPathTiles.size() < 1) {
					mCurrentJob->cancelReserve();
					mCurrentJob = nullptr;
					return;
				}
				mGoalTile = mPathTiles._Get_container().front();
				getNextTile();
			}
		}
		else {
			// Have items in hand, bring them to job
			// FIXME: empty unnecessary items
			if (mTile == mCurrentJob->getTile()) {
				mCurrentJob->fillRequirement(mItem.get());
				mItem.reset(nullptr);
				mGoalTile = nullptr;
			}
			else if (mNextTile == nullptr) {
				mGoalTile = mCurrentJob->getTile();
				mPathTiles = PathFinder::FindPath(mTile, mGoalTile);
				getNextTile();
			}

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
	if (mNextTile == mTile) {
		mNextTile = nullptr;
		return;
	}
	if (mNextTile->getCharacter() != mTile->getCharacter()) {
		if (mNextTile->isReservableForCharacter()) {
			mNextTile->reserveFor(mTile->getCharacter());
		}
		else {
			return; // If reserved by someone else
		}
	}

	if (mMoveCounter.expired()) {
		// At next tile, update tiles
		mTile->clearCharater();
		mNextTile->moveTo();

		// Update character
		mTile = mNextTile;
		getNextTile();
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
	}
}

void Character::doJob()
{
	if (mCurrentJob != nullptr) {
		if (mCurrentJob->doWork()) {
			mCurrentJob->cancelJob();
			mCurrentJob = nullptr;
		}
	}
}
