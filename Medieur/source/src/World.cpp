#include "World.h"

#include <string>
#include <memory>
#include <iostream>
#include <stdexcept>

#include "Tile.h"
#include "units.h"
#include "Character.h"
#include "Prototypes.h"
#include "JobManager.h"
#include "GroundEntity.h"
#include "PickableItem.h"
#include "IGroundEntityModule.h"


using namespace Prototypes;

// static
World* World::GenerateTestWorld()
{
	World* world = new World(units::kWorldWidth, units::kWorldHeight);

	for (int x = 0; x < units::kWorldWidth; x++)
	{
		world->mTiles.push_back(std::vector<Tile>());
		for (int y = 0; y < units::kWorldHeight; y++)
		{
			Tile tempTile(getTilePrototypeByName("GrassTile"), world, x, y);
			world->mTiles[x].push_back(tempTile);
		}
	}

	for (int i = 0; i < 5; i++)
	{
		world->createGroundEntity(5 + i, 5, getIdByName("Wall"));
		world->createGroundEntity(5, 5 + i, getIdByName("Wall"));
		world->createGroundEntity(5 + i, 9, getIdByName("Wall"));
		world->createGroundEntity(9, 5 + i, getIdByName("Wall"));

		/*for (int j = 0; j < 5; j++) {
			world->createGroundEntity(5 + i, 11 + j, getPrototypeByName("Plant"));
		}*/
	}
	world->createGroundEntity(5, 11, getIdByName("Plant"));
	world->createGroundEntity(6, 11, getIdByName("Plant"));

	world->getTile(7, 5)->clearGroundEntity();
	world->createGroundEntity(7, 5, getIdByName("Door"));
	return world;
}

World::World(const unsigned int width, const unsigned int height)
	:
	mJobManager(new JobManager())
{
	// Reserve the memory required
	mTiles.reserve(units::kWorldWidth);
	for (auto it : mTiles) {
		it.reserve(units::kWorldHeight);
	}
}

World::~World() {
	printf("chars size: %i\n", mCharacters.size());
}

Tile* World::getTile(const int pX, const int pY)
{
	if (pX < 0 || pX > getWidth() - 1 || pY < 0 || pY > getHeight() - 1) {
		printf("Invalid GetTile %ix%i\n", pX, pY);
		throw std::invalid_argument("Invalid argument");
	}
	return &mTiles[pX][pY];
}


size_t World::getHeight() const
{
	return mTiles[0].size();
}

void World::update()
{
	for (auto it : mCharacters) {
		it->update();
	}
	for (auto it = mGroundEntities.begin(); it != mGroundEntities.end();) {
		if (it->second.expired()) {
			it = mGroundEntities.erase(it);
		}
		else {
			if (it->first->mModule) {
				it->first->mModule->update();
			}
			it++;
		}
	}
}


void World::deleteItem(PickableItem * pItem)
{
	auto iters = mItems.equal_range(pItem->getId());
	for (auto it = iters.first; it != iters.second; it++) {
		if (it->second.get() == pItem) {
			if (it->second->mTile != nullptr) {
				it->second->mTile->clearItem(pItem);
			}
			else if (it->second->mCharacter != nullptr) {
				it->second->mCharacter->clearItem();
			}
			it->second.release();
			mItems.erase(it);
			break;
		}
	}
}


Character* World::createCharacter(int pX, int pY, int pId)
{
	Tile* tempTile = getTile(pX, pY);
	if (tempTile->isReservableForCharacter() == false) {
		throw std::invalid_argument("Tile already reserved by something!");
		return nullptr;
	}
	Character* pPrototype = Prototypes::getCharacterPrototypeById(pId);
	std::shared_ptr<Character> tempChar = std::make_shared<Character>(pPrototype, this, tempTile, pX, pY);
	mCharacters.push_back(tempChar);

	tempTile->reserveFor(tempChar.get());
	tempTile->moveTo();
	return tempChar.get();
}

GroundEntity* World::createGroundEntity(int pX, int pY, int pId)
{
	GroundEntity* pPrototype = Prototypes::getGroundEntityPrototypeById(pId);
	Tile* tempTile = getTile(pX, pY);
	if (tempTile->hasGroundEntity()) {
		//throw std::invalid_argument("Tile already reserved by something!");
		return nullptr;
	}
	std::shared_ptr<GroundEntity> newGroundEntity = std::make_shared<GroundEntity>(pPrototype, tempTile);
	if (pPrototype->mModule) {
		newGroundEntity->mModule = std::unique_ptr<IGroundEntityModule>(
			pPrototype->mModule->clone(pPrototype->mModule.get(), newGroundEntity.get())
			);
	}
	tempTile->setGroundEntity(newGroundEntity);
	mGroundEntities[newGroundEntity.get()] = newGroundEntity;
	return newGroundEntity.get();
}

Tile* World::createTile(int pX, int pY, int pId)
{
	// TODO:
	return getTile(1, 1);
}

PickableItem* World::createPickableItem(int pId, const int pAmount)
{
	PickableItem* pPrototype = Prototypes::getPickableItemPrototypeById(pId);
	PickableItem* newItem = new PickableItem(pPrototype, pAmount);
	mItems.insert(ItemMap::value_type(newItem->getId(), std::unique_ptr<PickableItem>(newItem)));
	return newItem;
}

JobManager * World::getJobManager()
{
	return mJobManager.get();
}
