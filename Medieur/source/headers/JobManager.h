#pragma once

#include <unordered_set>
#include <memory>

class Tile;
class Job;

class JobManager {
public:
	JobManager() {}
	~JobManager();
	// Adds to lists. Delete pointer thru job or manager
	void createJob(Job* pJob);
	// Delete's the memory, be sure to clean pointers to pJob
	void deleteJob(Job* pJob);
	// Returns nullptr if no available jobs
	Job* getJob();
	void removeJobFromOpen(Job* pJob);
	void addJobToOpen(Job* pJob);
	bool hasJobs() { return mOpenJobs.size() > 0; }
private:
	std::unordered_set<Job*> mAllJobs;
	std::unordered_set<Job*> mOpenJobs;
};