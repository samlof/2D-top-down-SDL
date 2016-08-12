#include "GroundEntityStockpileModule.h"

#include <functional>

#include "GroundEntity.h"
#include "Tile.h"
#include "InventoryItem.h"
#include "Character.h"
#include "Job.h"
#include "JobManager.h"
#include "World.h"

GroundEntityStockpileModule::GroundEntityStockpileModule(GroundEntityStockpileModule * pPrototype, GroundEntity * pThisEntity)
	:
	IGroundEntityModule(pThisEntity)
{
}

GroundEntityStockpileModule::GroundEntityStockpileModule(const int pDropItemId)
	:
	IGroundEntityModule(nullptr)
{
}

GroundEntityStockpileModule::~GroundEntityStockpileModule() = default;

void GroundEntityStockpileModule::createJob()
{
	Tile* thisTile = mThisEntity->getTile();
	Job::TargetFunc tfunc = [thisTile]() { return thisTile; };
	Job::JobFunc jfunc = []() { /* update func */ };
	Job* job = new Job(tfunc, jfunc);
	job->addChangedFunc(std::bind(&GroundEntityStockpileModule::stockChanged, this));
	// Add to jobmanager
	mThisEntity->getTile()->getWorld()->getJobManager()->createJob(job);
	mJob = job;

}

void GroundEntityStockpileModule::stockChanged()
{
	for (auto it : *mJob->getRequirements()) {
		if (it->isEmpty() == false) {
			it->changeMax(it->getMaxAmount()-it->getAmount());
			mThisEntity->getTile()->addItem(it);
		}
	}
}

void GroundEntityStockpileModule::update()
{
}