#pragma once

#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>

#include "Point.h"

class Job;
class Tile;
class Character;
class GroundEntity;
class PickableItem;

class World
{
public:
	// Statics
	static World* GenerateTestWorld();

	World(const unsigned int width, const unsigned int height);
	~World();

	Tile* getTile(const int pX, const int pY);

	size_t getWidth() const { return mTiles.size(); }
	size_t getHeight() const;

	void update();

	void createJob(Job* pJob);
	void deleteJob(Job* pJob);
	Job* getJob();
	bool hasJobs() { return mCurrentJobs.size() > 0; }

	void deleteItem(PickableItem* pItem);
	void addItem(PickableItem* pItem);

	void createCharacter(int pX, int pY, Character* pPrototype);
	void createGroundEntity(int pX, int pY, GroundEntity* pPrototype);
	void createTile(int pX, int pY, Tile* pPrototype);
	void createPickableItem(int pX, int pY, PickableItem* pPrototype);
private:
	std::vector<std::vector<Tile> > mTiles;
	std::vector<std::shared_ptr<Character> > mCharacters;
	std::unordered_map<GroundEntity*, std::weak_ptr<GroundEntity> > mGroundEntities;
	std::unordered_set<Job*> mCurrentJobs;

	using ItemMap = std::unordered_multimap<int, PickableItem*>;
	ItemMap mItems;
};