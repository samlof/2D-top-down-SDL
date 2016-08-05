#include "World.h"

#include <stdexcept>

#include <map>
#include <string>
#include <memory>
#include <boost\algorithm\clamp.hpp>
#include <iostream>

#include "Tile.h"
#include "units.h"
#include "GroundEntity.h"
#include "Character.h"
#include "Prototypes.h"
#include "job.h"

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
			world->mTiles[x].push_back(Tile(world, TileType::GRASS, x, y));
		}
	}

	for (int i = 0; i < 5; i++)
	{
		world->createGroundEntity(5 + i, 5, getPrototypeByName("Wall"));
		world->createGroundEntity(5, 5 + i, getPrototypeByName("Wall"));
		world->createGroundEntity(5 + i, 9, getPrototypeByName("Wall"));
		world->createGroundEntity(9, 5 + i, getPrototypeByName("Wall"));

		/*for (int j = 0; j < 5; j++) {
			world->createGroundEntity(5 + i, 11 + j, getPrototypeByName("Plant"));
		}*/
	}
	world->createGroundEntity(5, 11, getPrototypeByName("Plant"));
	world->createGroundEntity(6, 11, getPrototypeByName("Plant"));


	world->getTile(7, 5)->clearGroundEntity();
	world->createGroundEntity(7, 5, getPrototypeByName("Door"));
	return world;
}

World::World(const unsigned int width, const unsigned int height)
{
	// Reserve the memory required
	mTiles.reserve(units::kWorldWidth);
	for (auto it : mTiles) {
		it.reserve(units::kWorldHeight);
	}
}


World::~World()
{
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

void World::createJob(Job * pJob)
{
	printf("Create Job!\n");
	mCurrentJobs.insert(pJob);
}

Job * World::getJob()
{
	for (auto it : mCurrentJobs) {
		return it;
	}
	throw "No jobs!";
	return nullptr;
}

void World::deleteJob(Job * pJob)
{
	mCurrentJobs.erase(pJob);
	delete pJob;
}

void World::createCharacter(int pX, int pY)
{
	std::shared_ptr<Character> tempChar = std::make_shared<Character>(this, getTile(pX, pY), pX, pY);
	mCharacters.push_back(tempChar);

	getTile(pX, pY)->reserveFor(tempChar);
	getTile(pX, pY)->moveTo();
	tempChar->setPathTo(getTile(6, 8));
}

void World::createGroundEntity(int pX, int pY, std::shared_ptr<GroundEntity> pPrototype)
{
	Tile* tempTile = getTile(pX, pY);
	if (tempTile->hasGroundEntity()) return;
	std::shared_ptr<GroundEntity> newGroundEntity = std::make_shared<GroundEntity>(pPrototype.get(), tempTile);
	if (pPrototype->mModule) {
		newGroundEntity->mModule = std::unique_ptr<IGroundEntityModule>(
			pPrototype->mModule->clone(newGroundEntity.get())
			);
	}
	tempTile->setGroundEntity(newGroundEntity);
	mGroundEntities[newGroundEntity.get()] = newGroundEntity;
}
