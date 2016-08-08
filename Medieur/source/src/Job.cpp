#include "Job.h"

#include "JobManager.h"
#include "Character.h"

#include <iostream>




Job::Job(JobManager & pManager, Tile * pTargetTile, JobFunc & pJobFunc)
	: mTargetTile(pTargetTile), mJobFunc(pJobFunc), mManager(pManager),
	mCharacter(nullptr)
{

}

Job::~Job() = default;

void Job::reserve(Character * pCharacter)
{
	if (isReserved()) throw "Job already reserved!";
	mCharacter = pCharacter;
	mManager.removeJobFromOpen(this);
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
	mManager.addJobToOpen(this);
}

void Job::cancelJob()
{
	clearCharacter();
	mManager.deleteJob(this);
}