#include "GroundEntityPlantModule.h"

#include <iostream>

#include "GroundEntity.h"
#include "Tile.h"
#include "Job.h"
#include "World.h"

#include "Prototypes.h" // TODO: remove this

namespace {
	const int kMaxGrowth = 5;
	const int kMaxHealth = 10;
	const int kGrowthSteps = 100;
	const int kHealthDropSteps = 300;
}

GroundEntityPlantModule::GroundEntityPlantModule(GroundEntity * pThisEntity)
	:
	IGroundEntityModule(pThisEntity),
	mHealth(kMaxHealth), mGrowth(1),
	mHealthCounter(kHealthDropSteps), mGrowthCounter(kGrowthSteps)
{
}

void GroundEntityPlantModule::update()
{
	mHealthCounter.step();
	mGrowthCounter.step();

	if (mHealthCounter.expired()) {
		mHealth--;
		mHealthCounter.pause(); // Remove
		if (mHealth == 5) {
			printf("Come interact!\n");
			Job* job = new Job(mThisEntity->getTile(), JobType::INTERACT);
			mThisEntity->getTile()->getWorld()->createJob(job);
		}
		else if (mHealth <= 0) {
			rot();
		}
		mHealthCounter.reset();
	}
	if (mGrowthCounter.expired()) {
		mGrowth++;
		if (mGrowth >= kMaxGrowth - 1) {
			printf("Come pickup!\n");
			Job* job = new Job(mThisEntity->getTile(), JobType::PICKUP);
			mThisEntity->getTile()->getWorld()->createJob(job);
			mGrowthCounter.pause(); // remove
		} else if (mGrowth > kMaxGrowth + 2) {
			rot();
		}
		mGrowthCounter.reset();
	}

}

void GroundEntityPlantModule::interact()
{
	printf("Interact: ");
	printf("x: %i, y: %i\n", mThisEntity->getTile()->getX(), mThisEntity->getTile()->getY());
	mHealth = kMaxHealth;
	mHealthCounter.reset();
}

void GroundEntityPlantModule::pickup()
{
	//if (mGrowth >= kMaxGrowth - 1) {
		printf("Create item!\n");
		Tile* const tempTile = mThisEntity->getTile();
		const int x = tempTile->getX();
		const int y = tempTile->getY();
		tempTile->getWorld()->createPickableItem(x, y, Prototypes::getIdByName("Item_Wheat"));
		mThisEntity->erase();
	/*}
	else {
		rot();
	}*/
}

void GroundEntityPlantModule::rot()
{
	mThisEntity->erase();
}