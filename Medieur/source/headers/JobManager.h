#pragma once

#include <unordered_set>
#include <memory>

class Job;

class JobManager {
public:
	JobManager() {}
	void createJob(Job* pJob);
	void deleteJob(Job* pJob);
	Job* getJob();
	bool hasJobs() { return mCurrentJobs.size() > 0; }
private:
	std::unordered_set<Job*> mCurrentJobs;
};