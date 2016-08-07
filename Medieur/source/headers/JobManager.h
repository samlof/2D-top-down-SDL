#pragma once

#include <unordered_set>
#include <memory>

class Tile;
class Job;

class JobManager {
public:
	JobManager() {}
	void createJob(Job* pJob);
	void deleteJob(Job* pJob);
	Job* getJob();
	void removeJobFromOpen(Job* pJob);
	void addJob(Job* pJob);
	bool hasJobs() { return mCurrentJobs.size() > 0; }
private:
	std::unordered_set<Job*> mCurrentJobs;
};