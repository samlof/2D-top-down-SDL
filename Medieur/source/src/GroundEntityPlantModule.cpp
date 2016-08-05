#include "GroundEntityPlantModule.h"

#include <iostream>

#include "GroundEntity.h"
#include "Tile.h"
#include "Job.h"
#include "World.h"

namespace {
	const int kMaxGrowth = 6;
	const int kMaxHealth = 6;
	const int kGrowthSteps = 2000;
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
		if (mHealth == 5) {
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
		if (mGrowth == kMaxGrowth) {
			Job* job = new Job(mThisEntity->getTile(), JobType::PICKUP);
			mThisEntity->getTile()->getWorld()->createJob(job);
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
	if (mGrowth == kMaxGrowth) {
		// TODO: pickup, inventories
	}
	else {
		rot();
	}
}

void GroundEntityPlantModule::rot()
{
	mThisEntity->erase();
}