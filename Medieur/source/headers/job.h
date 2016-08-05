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

private:
	Tile* mTargetTile;
	JobType mJobType;
	bool mReserved;
};