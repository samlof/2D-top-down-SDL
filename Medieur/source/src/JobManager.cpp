#include "JobManager.h"

#include "Job.h"
#include "Character.h"

void JobManager::deleteJob(Job * pJob)
{
	pJob->clearCharacter();
	mCurrentJobs.erase(pJob);
	delete pJob;
}

Job* JobManager::createJob(Tile* pTargetTile, Job::JobFunc pJobFunc)
{
	printf("Create Job!\n");
	Job* job = new Job(*this, pTargetTile, pJobFunc);
	mCurrentJobs.insert(job);
	return job;
}

Job * JobManager::getJob()
{
	for (auto it : mCurrentJobs) {
		return it;
	}
	return nullptr;
}

void JobManager::removeJobFromOpen(Job * pJob)
{
	mCurrentJobs.erase(pJob);
}

void JobManager::addJob(Job * pJob)
{
	mCurrentJobs.insert(pJob);
}
