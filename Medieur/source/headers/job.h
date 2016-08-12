#pragma once

#include <functional>
#include <queue>

class Tile;
class Character;
class JobManager;

class Job {
public:
	using JobFunc = std::function<void(Character*)>;
	using TargetFunc = std::function<Tile*(void)>;
	Job(TargetFunc& pTargetFunc, JobFunc& pJobFunc);
	~Job();
	void setManager(JobManager* pManager) { mManager = pManager; }

	void addFunc(TargetFunc& pTargetFunc, JobFunc& pFunc);
	void reserve(Character* pCharacter);
	bool isReserved() const { return mCharacter != nullptr; }
	void clearCharacter();
	void cancelReserve();
	// Doesn't clear the creator, so be sure that one is cleared before
	void cancelJob();

	Tile* getTile() { return mTargetTiles.front()(); }
	JobFunc getNextFunc() { return mJobFuncs.front(); }
	// Returns true if job is done, false if more to do
	bool popFunc();
private:
	JobManager* mManager;
	// TODO: use the creator, so if target moves this can adapt
	std::queue<TargetFunc> mTargetTiles;
	std::queue<JobFunc> mJobFuncs;
	Character* mCharacter;
};