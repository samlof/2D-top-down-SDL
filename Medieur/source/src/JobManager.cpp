#include "JobManager.h"

#include "Job.h"
#include "Character.h"

void JobManager::deleteJob(Job * pJob)
{
	mCurrentJobs.erase(pJob);
	delete pJob;
}

void JobManager::createJob(Job* pJob)
{
	printf("Create Job!\n");
	mCurrentJobs.insert(pJob);
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
