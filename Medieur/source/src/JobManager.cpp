#include "JobManager.h"

#include <stdexcept>

#include "Job.h"
#include "Character.h"

void JobManager::deleteJob(Job * pJob)
{
	if (pJob == nullptr) {
		throw std::invalid_argument("Trying to delete a null job!");
	}

	mAllJobs.erase(pJob);
	mOpenJobs.erase(pJob);
	delete pJob;
}

JobManager::~JobManager()
{
	for (auto it : mAllJobs) {
		delete it;
	}
	mAllJobs.clear();
	mOpenJobs.clear();
}

void JobManager::createJob(Job* pJob)
{
	printf("Create Job!\n");
	mAllJobs.insert(pJob);
	mOpenJobs.insert(pJob);
}

Job * JobManager::getJob()
{
	for (auto it : mOpenJobs) {
		return it;
	}
	return nullptr;
}

void JobManager::removeJobFromOpen(Job * pJob)
{
	mOpenJobs.erase(pJob);
}

void JobManager::addJobToOpen(Job * pJob)
{
	mOpenJobs.insert(pJob);
}