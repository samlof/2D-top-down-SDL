#pragma once

#include <unordered_set>
#include <memory>

#include "Job.h"

class Tile;

class JobManager {
public:
	JobManager() {}
	Job* createJob(Tile* pTargetTile, Job::JobFunc pJobFunc);
	void deleteJob(Job* pJob);
	Job* getJob();
	void removeJobFromOpen(Job* pJob);
	void addJob(Job* pJob);
	bool hasJobs() { return mCurrentJobs.size() > 0; }
private:
	std::unordered_set<Job*> mCurrentJobs;
};