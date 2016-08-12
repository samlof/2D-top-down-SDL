#include "Job.h"

#include "JobManager.h"
#include "Character.h"

#include <iostream>




Job::Job(JobManager* pManager, TargetFunc& pTargetFunc, JobFunc& pJobFunc)
	: mManager(pManager), mCharacter(nullptr)
{
	mTargetTiles.push(pTargetFunc);
	mJobFuncs.push(pJobFunc);
}

Job::Job(TargetFunc & pTargetFunc, JobFunc & pJobFunc)
	: mManager(nullptr), mCharacter(nullptr)
{
	mTargetTiles.push(pTargetFunc);
	mJobFuncs.push(pJobFunc);
}


Job::~Job() = default;

void Job::addFunc(TargetFunc & pTargetFunc, JobFunc & pFunc)
{
	mTargetTiles.push(pTargetFunc);
	mJobFuncs.push(pFunc);
}

void Job::reserve(Character * pCharacter)
{
	if (isReserved()) throw "Job already reserved!";
	mCharacter = pCharacter;
	mManager->removeJobFromOpen(this);
}

void Job::clearCharacter()
{
	if (mCharacter == nullptr) return;
	mCharacter->cancelPath();
	mCharacter->clearJob();
	mCharacter = nullptr;
}

void Job::cancelReserve()
{
	clearCharacter();
	mManager->addJobToOpen(this);
}

void Job::cancelJob()
{
	clearCharacter();
	mManager->deleteJob(this);
}

Tile * Job::getTile()
{
	return mTargetTiles.front()();
}

Job::JobFunc Job::getNextFunc()
{
	return mJobFuncs.front();
}

bool Job::popFunc()
{
	mJobFuncs.pop();
	mTargetTiles.pop();
	if (mJobFuncs.empty()) {
		return true;
	}
	else {
		return false;
	}
}
