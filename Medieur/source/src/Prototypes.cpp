#include "Prototypes.h"

#include <map>

#include "SpriteManager.h"
#include "GroundEntity.h"
#include "Rectangle.h"
#include "units.h"
#include "GroundEntityPlantModule.h"
#include "Sprite.h"
#include "PickableItem.h"
#include "Tile.h"

namespace Prototypes {
	namespace {
		std::map<int, std::unique_ptr<GroundEntity> > groundEntityPrototypes;
		std::map<int, std::unique_ptr<PickableItem> > pickableItemPrototypes;
		std::map<int, std::unique_ptr<Tile> > tilePrototypes;
		std::map<std::string, int> idsByName;

		int idCount = 0;
		// constants
		const Rectangle kWallSource(224, 384, 32, 32);
		const Rectangle kDoorSource(0, 0, 32, 32);
		const Rectangle kPlantSource(units::kTileSize * 6, 0, units::kTileSize, 64);
	}

	bool createPrototypes() {
		createGroundEntityPrototype("Door", 1, new Sprite("bad_door.png", kDoorSource));
		createGroundEntityPrototype("Wall", 0, new Sprite("walls1.png", kWallSource));
		createGroundEntityPrototype("Plant", 1, new Sprite("plants.png", kPlantSource));
		getGroundEntityPrototypeByName("Plant")->mModule = std::make_unique<GroundEntityPlantModule>(
			getGroundEntityPrototypeByName("Plant")
			);


		SpriteManager::setGroundEntityFunction(getIdByName("Plant"),
			[](GroundEntity* pGrEntity) {
			int growth = static_cast<GroundEntityPlantModule*>(pGrEntity->mModule.get())->getGrowth();
			Rectangle newRect = kPlantSource;
			newRect.addY((growth - 1) * 64);
			return newRect;
		});


		SpriteManager::initSprites(); // FIXME: tile and character prototypes
		return true;
	}

	void createGroundEntityPrototype(
		const std::string & pName, const float pMovSpeed, // Entity stuff
		Sprite* pSprite)
	{
		int id = getNextId();
		SpriteManager::createSprite(id, pSprite);
		groundEntityPrototypes[id] = std::make_unique<GroundEntity>(id, pMovSpeed);
		idsByName[pName] = id;
	}

	GroundEntity* getGroundEntityPrototypeByName(const std::string & pName)
	{
		return getGroundEntityPrototypeById(idsByName[pName]);
	}

	GroundEntity* getGroundEntityPrototypeById(const int id)
	{
		return groundEntityPrototypes.at(id).get();
	}

	void createPickableItemPrototype(const std::string & pName, const float pMovSpeed, Sprite * pSprite)
	{
		int id = getNextId();
		SpriteManager::createSprite(id, pSprite);
		pickableItemPrototypes[id] = std::make_unique<PickableItem>(id);
		idsByName[pName] = id;
	}

	PickableItem * getPickableItemPrototypeByName(const std::string & pName)
	{
		return getPickableItemPrototypeById(idsByName[pName]);
	}

	PickableItem * getPickableItemPrototypeById(const int id)
	{
		return pickableItemPrototypes.at(id).get();
	}

	void createTilePrototype(const std::string & pName, const float pMovSpeed, Sprite * pSprite)
	{
		int id = getNextId();
		SpriteManager::createSprite(id, pSprite);
		tilePrototypes[id] = std::make_unique<Tile>(id,TileType::GRASS);
		idsByName[pName] = id;
	}

	Tile * getTilePrototypeByName(const std::string & pName)
	{
		return getTilePrototypeById(idsByName[pName]);
	}

	Tile * getTilePrototypeById(const int id)
	{
		return tilePrototypes.at(id).get();
	}

	int getIdByName(const std::string & pName)
	{
		return idsByName[pName];
	}

	int getNextId()
	{
		return idCount++;
	}
}
