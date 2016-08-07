#pragma once

#include <unordered_set>
#include <memory>

class Tile;
class Job;

class JobManager {
public:
	JobManager() {}
	~JobManager();
	void createJob(Job* pJob);
	void deleteJob(Job* pJob);
	Job* getJob();
	void removeJobFromOpen(Job* pJob);
	void addJobToOpen(Job* pJob);
	bool hasJobs() { return mOpenJobs.size() > 0; }
private:
	std::unordered_set<Job*> mAllJobs;
	std::unordered_set<Job*> mOpenJobs;
};