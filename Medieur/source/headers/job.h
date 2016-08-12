#pragma once

#include <functional>
#include <vector>

class Tile;
class Character;
class JobManager;
class InventoryItem;

class Job {
public:
	using JobFunc = std::function<void(void)>;
	using TargetFunc = std::function<Tile*(void)>;
	using ChangedFunc = std::function<void(void)>;

	Job(TargetFunc& pTargetFunc, JobFunc& pJobFunc, std::vector<InventoryItem*> pRequirements);
	Job(TargetFunc& pTargetFunc, JobFunc& pJobFunc);
	~Job();
	void setManager(JobManager* pManager) { mManager = pManager; }
	void addChangedFunc(ChangedFunc pFunc) { mChangedFunc.push_back(pFunc); }

	// Character functions
	void reserve(Character* pCharacter);
	bool isReserved() const { return mCharacter != nullptr; }
	void clearCharacter();
	void cancelReserve();

	// Doesn't clear the creator, so be sure that one is cleared before
	void cancelJob();

	// Requirements functions
	bool hasAllMaterials();
	InventoryItem* getRequirement();
	std::vector<InventoryItem*>* getRequirements() { return &mRequirements; }

	void fillRequirement(InventoryItem* pItem);
	void addReq(const int pId, const int pAmount);

	Tile* getTile() { return mTargetTile(); }

	// Returns true if done, false if more work necessary
	bool doWork();
private:
	int mJobRequiredTime, mJobTime;
	JobManager* mManager;
	std::vector<InventoryItem*> mRequirements;
	TargetFunc mTargetTile;
	JobFunc mJobFunc;
	std::vector<ChangedFunc> mChangedFunc;
	Character* mCharacter;
};