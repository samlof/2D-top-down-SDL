#pragma once

enum class JobType
{
	PICKUP,
	INTERACT
};

class Tile;

class Job {
public:
	Job(Tile* pTargetTile, JobType pJobType) : mTargetTile(pTargetTile), mJobType(pJobType)
	{}

	void reserve() { if (mReserved) throw "Job already reserved!"; mReserved = true; }
	bool isReserved() const { return mReserved; }
	Tile* getTile() { return mTargetTile; }
	JobType getType() { return mJobType; }
private:
	Tile* mTargetTile;
	JobType mJobType;
	bool mReserved;
};