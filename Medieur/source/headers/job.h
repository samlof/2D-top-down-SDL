#pragma once

#include <functional>
#include <vector>

class Tile;
class Character;
class JobManager;
class InventoryItem;

class Job {
public:
	using JobFunc = std::function<void(Character*)>;
	using TargetFunc = std::function<Tile*(void)>;
	Job(TargetFunc& pTargetFunc, JobFunc& pJobFunc, std::vector<InventoryItem*> pRequirements);
	Job(TargetFunc& pTargetFunc, JobFunc& pJobFunc);
	~Job();
	void setManager(JobManager* pManager) { mManager = pManager; }

	// Character functions
	void reserve(Character* pCharacter);
	bool isReserved() const { return mCharacter != nullptr; }
	void clearCharacter();
	void cancelReserve();

	// Doesn't clear the creator, so be sure that one is cleared before
	void cancelJob();

	// Requirements functions
	bool hasRequirements();
	InventoryItem* getRequirement();
	void fillRequirement(InventoryItem* pItem);

	Tile* getTile() { return mTargetTile(); }

	// Returns true if done, false if more work necessary
	bool doWork();
private:
	int mJobRequiredTime, mJobTime;
	JobManager* mManager;
	std::vector<InventoryItem*> mRequirements;
	TargetFunc mTargetTile;
	JobFunc mJobFunc;
	Character* mCharacter;
};