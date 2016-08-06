#pragma once

#include <functional>

class Tile;
class Character;
class JobManager;

class Job {
public:
	using JobFunc = std::function<void(Character*)>;
	Job(JobManager& pManager, Tile* pTargetTile, JobFunc pJobFunc)
		: mTargetTile(pTargetTile), mJobFunc(pJobFunc),	mManager(pManager)
	{}

	void reserve() { if (mReserved) throw "Job already reserved!"; mReserved = true; }
	bool isReserved() const { return mReserved; }
	void cancelJob();
	Tile* getTile() { return mTargetTile; }
	JobFunc getFunc() { return mJobFunc; }
private:
	JobManager& mManager;
	Tile* mTargetTile;
	JobFunc mJobFunc;
	bool mReserved;
};