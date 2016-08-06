#include "Job.h"

#include "JobManager.h"


void Job::reserve(Character * pCharacter)
{
	if (isReserved()) throw "Job already reserved!";
	mCharacter = pCharacter;
	mManager.removeJobFromOpen(this);
}

void Job::cancelReserve(Character * pCharacter)
{
	if (mCharacter == pCharacter) {
		mCharacter = nullptr;
		mManager.addJob(this);
	}
}

void Job::cancelJob()
{
	mManager.deleteJob(this);
}