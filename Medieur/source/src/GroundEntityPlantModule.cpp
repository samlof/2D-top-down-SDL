#include "GroundEntityPlantModule.h"

#include <iostream>

#include "GroundEntity.h"
#include "Tile.h"

namespace {
	const int kMaxGrowth = 6;
	const int kMaxHealth = 10;
	const int kGrowthSteps = 200;
	const int kHealthDropSteps = 300;
}

GroundEntityPlantModule::GroundEntityPlantModule(GroundEntity & pThisEntity)
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
		if (mHealth < 5) {
			mThisEntity.getTile()->getCharacter()
		}
		if (mHealth <= 0) {
			rot();
		}
		mHealthCounter.reset();
	}
	if (mGrowthCounter.expired()) {
		mGrowth++;
		if (mGrowth > kMaxGrowth) {
			rot();
		}
		mGrowthCounter.reset();
	}

}

void GroundEntityPlantModule::interact()
{
	printf("Interact: ");
	printf("x: %i, y: %i\n", mThisEntity.getTile()->getX(), mThisEntity.getTile()->getY());
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
	mThisEntity.erase();
}