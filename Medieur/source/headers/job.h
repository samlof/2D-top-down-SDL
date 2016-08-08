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
	// Doesn't clear the creator, so only call from it
	void cancelJob();

	Tile* getTile() { return mTargetTile; }
	JobFunc getFunc() { return mJobFunc; }
private:
	JobManager& mManager;
	// TODO: use the creator, so if target moves this can adapt
	Tile* mTargetTile;
	JobFunc mJobFunc;
	Character* mCharacter;
};