#include "GroundEntityPlantModule.h"

#include <iostream>

#include "GroundEntity.h"
#include "Tile.h"
#include "Job.h"
#include "World.h"
#include "Character.h"
#include "JobManager.h"
#include "ItemManager.h"
#include "InventoryItem.h"

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

GroundEntityPlantModule::~GroundEntityPlantModule() = default;

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
			mGrowthCounter.pause(); // TODO: fix growth and health counter constants
		}
		else if (mGrowth > kMaxGrowth + 2) {
			rot();
		}
		mGrowthCounter.reset();
	}

}

void GroundEntityPlantModule::interact(Character* pCharacter)
{
	if (mInteractJob != nullptr) {
		mInteractJob->cancelJob();
		mInteractJob = nullptr;
	}
	if (pCharacter == nullptr) return;

	printf("Interact: ");
	printf("x: %i, y: %i\n", mThisEntity->getTile()->getX(), mThisEntity->getTile()->getY());
	mHealth = kMaxHealth;
	mHealthCounter.reset();
}

void GroundEntityPlantModule::pickup(Character* pCharacter)
{
	if (mPickupJob != nullptr) {
		mPickupJob->cancelJob();
		mPickupJob = nullptr;
	}
	if (pCharacter == nullptr) return;

	if (mGrowth >= kMaxGrowth - 1) {
		printf("Pickup item: ");
		printf("x: %i, y: %i\n", mThisEntity->getTile()->getX(), mThisEntity->getTile()->getY());

		InventoryItem* item = ItemManager::createLocalPickableItem(
			mDropItemId, kHarvestAmount
		);

		pCharacter->addItem(item);
		if (item->isEmpty() == false) {
			mThisEntity->getTile()->addItem(item);
		}
		delete item;
		rot();
	}
	else {
		rot();
	}
}

void GroundEntityPlantModule::cleanJobs()
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

void GroundEntityPlantModule::rot()
{
	cleanJobs();
	mThisEntity->erase();
}

#undef CREATEFUNC // Undef the helper macro