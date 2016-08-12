#pragma once

#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>

class Tile;
class Character;
class GroundEntity;
class InventoryItem;
class JobManager;
class ItemManager;

class World
{
public:
	// Statics
	static World* GenerateTestWorld();

	World(const int width, const int height);
	~World();

	Tile* getTile(const int pX, const int pY);

	size_t getWidth() const { return mTiles.size(); }
	size_t getHeight() const;

	void update();
	

	Character* createCharacter(int pX, int pY, int pId);
	GroundEntity* createGroundEntity(int pX, int pY, int pId);
	// TODO: make into changeTile?
	Tile* createTile(int pX, int pY, int pId);

	ItemManager* getItemManager() {	return mItemManager.get();	}
	JobManager* getJobManager() { return mJobManager.get(); }
private:
	std::vector<std::vector<Tile> > mTiles;
	std::vector<std::shared_ptr<Character> > mCharacters;
	std::unordered_map<GroundEntity*, std::weak_ptr<GroundEntity> > mGroundEntities;

	std::unique_ptr<JobManager> mJobManager;
	std::unique_ptr<ItemManager> mItemManager;
};