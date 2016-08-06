#include "Job.h"

#include "JobManager.h"
#include "Character.h"

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
	mCharacter = nullptr;
	mManager.addJob(this);
}

void Job::cancelJob()
{
	mManager.deleteJob(this);
}