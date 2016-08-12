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
	// First create job to pick them up

	// TODO: function to find items
	Tile* tileWithItems = mThisEntity->getTile();
	Job::TargetFunc tfunc = [tileWithItems]() { return tileWithItems; };
	Job::JobFunc jfunc = [tileWithItems](Character* pCharacter) { return; };
	Job* job = new Job(tfunc, jfunc);

	// Second add job to drop item here
	Tile* thisTile = mThisEntity->getTile();
	Job::TargetFunc t2func = [thisTile]() { return thisTile; };
	std::function<void(InventoryItem*)> tempFunc = std::bind(&Tile::addItem, thisTile, std::placeholders::_1);
	Job::JobFunc j2func = [tempFunc](Character* pChar) {
		tempFunc(pChar->getItem()); };
	job->addFunc(t2func, j2func);

	// Add to jobmanager
	mThisEntity->getTile()->getWorld()->getJobManager()->createJob(job);
	
}

void GroundEntityStockpileModule::update()
{
	for (auto it : mItems) {

	}
}

void GroundEntityStockpileModule::interact(Character * pCharacter)
{
}

void GroundEntityStockpileModule::pickup(Character * pCharacter)
{
}
