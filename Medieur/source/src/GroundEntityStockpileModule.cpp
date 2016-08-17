#include "GroundEntityStockpileModule.h"

#include <functional>

#include "GroundEntity.h"
#include "Tile.h"
#include "InventoryItem.h"
#include "ItemManager.h"
#include "Character.h"
#include "Job.h"
#include "JobManager.h"
#include "World.h"

GroundEntityStockpileModule::GroundEntityStockpileModule(GroundEntityStockpileModule * pPrototype, GroundEntity * pThisEntity)
	:
	IGroundEntityModule(pThisEntity), mItems(pPrototype->mItems)
{
}

GroundEntityStockpileModule::GroundEntityStockpileModule()
	:
	IGroundEntityModule(nullptr)
{
}

GroundEntityStockpileModule::~GroundEntityStockpileModule() = default;

void GroundEntityStockpileModule::createJob()
{
	if (mItems.empty()) return;
	if (mJob != nullptr) {
		// TODO: update job or something
		return;
	}
	Tile* thisTile = mThisEntity->getTile();
	Job::TargetFunc tfunc = [thisTile]() { return thisTile; };
	Job::JobFunc jfunc = []() {};
	Job* job = new Job(tfunc, jfunc);
	job->addChangedFunc(std::bind(&GroundEntityStockpileModule::stockChanged, this));
	// Add to jobmanager
	mThisEntity->getTile()->getWorld()->getJobManager()->createJob(job);
	mJob = job;

	for (auto it : mItems) {
		mJob->addReq(it, 0);
	}
}

void GroundEntityStockpileModule::stockChanged()
{
	for (auto it : *mJob->getRequirements()) {
		// TODO: check if took stuff

		// Check if added stuff.
		if (it->isEmpty() == false) {
			const int amount = it->getAmount();
			mThisEntity->getTile()->addItem(it);
			it->changeMax(it->getMaxAmount() - amount);
		}
	}
}