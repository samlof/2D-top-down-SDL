#pragma once

#include <functional>

class Tile;
class Character;
class JobManager;

class Job {
public:
	using JobFunc = std::function<void(Character*)>;
	Job(JobManager& pManager, Tile* pTargetTile, JobFunc& pJobFunc)
		: mTargetTile(pTargetTile), mJobFunc(pJobFunc),	mManager(pManager),
		mCharacter(nullptr)
	{}
	Job(JobManager& pManager, Tile* pTargetTile, JobFunc&& pJobFunc)
		: mTargetTile(pTargetTile), mJobFunc(std::move(pJobFunc)), mManager(pManager),
		mCharacter(nullptr)
	{}
	~Job();

	void reserve(Character* pCharacter);
	bool isReserved() const { return mCharacter != nullptr; }
	void clearCharacter();
	void cancelReserve();
	void cancelJob();
	Tile* getTile() { return mTargetTile; }
	JobFunc getFunc() { return mJobFunc; }
private:
	JobManager& mManager;
	Tile* mTargetTile;
	JobFunc mJobFunc;
	Character* mCharacter;
};