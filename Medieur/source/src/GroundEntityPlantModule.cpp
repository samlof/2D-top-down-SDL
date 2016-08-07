#include "GroundEntityPlantModule.h"

#include <iostream>

#include "GroundEntity.h"
#include "Tile.h"
#include "Job.h"
#include "World.h"
#include "JobManager.h"
#include "Character.h"

#define CREATEFUNC(x) std::bind(&GroundEntityPlantModule::##x, this, std::placeholders::_1)
namespace {
	const int kMaxGrowth = 5;
	const int kMaxHealth = 10;
	const int kGrowthSteps = 100;
	const int kHealthDropSteps = 3000;

	const int kHarvestAmount = 3;
}

GroundEntityPlantModule::GroundEntityPlantModule(
	GroundEntityPlantModule * pPrototype, GroundEntity * pThisEntity)
	:
	IGroundEntityModule(pThisEntity),
	mHealth(pPrototype->mHealth), mGrowth(pPrototype->mGrowth), mDropItemId(pPrototype->mDropItemId),
	mHealthCounter(kHealthDropSteps), mGrowthCounter(kGrowthSteps),
	mInteractJob(nullptr), mPickupJob(nullptr)
{
}

GroundEntityPlantModule::~GroundEntityPlantModule()
{
	if (mInteractJob != nullptr) {
		mInteractJob->cancelJob();
		mInteractJob = nullptr;
	}
	if (mPickupJob != nullptr) {
		mPickupJob->cancelJob();
		mPickupJob = nullptr;
	}
}

GroundEntityPlantModule::GroundEntityPlantModule(const int pDropItemId)
	:
	IGroundEntityModule(nullptr),
	mHealth(kMaxHealth), mGrowth(1), mDropItemId(pDropItemId),
	mHealthCounter(kHealthDropSteps), mGrowthCounter(kGrowthSteps)
{}

void GroundEntityPlantModule::update()
{
	mHealthCounter.step();
	mGrowthCounter.step();

	if (mHealthCounter.expired()) {
		mHealth--;
		if (mHealth == 5 && (mInteractJob == nullptr)) {
			Job::JobFunc func = CREATEFUNC(interact);
			JobManager* jobManager = mThisEntity->getTile()->getWorld()->getJobManager();
			mInteractJob = new Job(*jobManager, mThisEntity->getTile(), func);
			jobManager->createJob(mInteractJob);
		}
		else if (mHealth <= 0) {
			rot();
		}
		mHealthCounter.reset();
	}
	if (mGrowthCounter.expired()) {
		mGrowth++;
		if (mGrowth >= kMaxGrowth - 1 && (mPickupJob == nullptr)) {
			Job::JobFunc func = CREATEFUNC(pickup);
			JobManager* jobManager = mThisEntity->getTile()->getWorld()->getJobManager();
			mPickupJob = new Job(*jobManager, mThisEntity->getTile(), func);
			jobManager->createJob(mPickupJob);
		}
		else if (mGrowth > kMaxGrowth + 2) {
			rot();
		}
		mGrowthCounter.reset();
	}

}

void GroundEntityPlantModule::interact(Character* pCharacter)
{
	printf("Interact: ");
	printf("x: %i, y: %i\n", mThisEntity->getTile()->getX(), mThisEntity->getTile()->getY());
	mHealth = kMaxHealth;
	mHealthCounter.reset();
	mInteractJob = nullptr;
}

void GroundEntityPlantModule::pickup(Character* pCharacter)
{
	if (mGrowth >= kMaxGrowth - 1) {
	printf("Pickup item: ");
	printf("x: %i, y: %i\n", mThisEntity->getTile()->getX(), mThisEntity->getTile()->getY());

	PickableItem* item = mThisEntity->getTile()->getWorld()->createPickableItem(mDropItemId, kHarvestAmount);

	pCharacter->addItem(item);
	mPickupJob = nullptr;
	mThisEntity->erase();
	}
	else {
		rot();
	}
}

void GroundEntityPlantModule::rot()
{
	mThisEntity->erase();
}

#undef CREATEFUNC