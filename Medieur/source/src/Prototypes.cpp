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
#include "Character.h"

namespace Prototypes {
	namespace {
		std::map<int, std::unique_ptr<GroundEntity> > groundEntityPrototypes;
		std::map<int, std::unique_ptr<PickableItem> > pickableItemPrototypes;
		std::map<int, std::unique_ptr<Character> > characterPrototypes;
		std::map<int, std::unique_ptr<Tile> > tilePrototypes;
		std::map<std::string, int> idsByName;

		int idCount = 0;
		// constants
		const Rectangle kWallSource(224, 384, 32, 32);
		const Rectangle kDoorSource(0, 0, 32, 32);
		const Rectangle kPlantSource(units::kTileSize * 6, 0, units::kTileSize, 64);
		const Rectangle kPlantItemSource(units::kTileSize * 6, 4 * 64, units::kTileSize, 64);
		const Rectangle kGrassSource(0, 0, 512, 512);
		const Rectangle kCharacterSource(0, 0, 32, 32);
	}

	bool createPrototypes() {
		// Ground entity prototypes
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

		// Tile prototype
		createTilePrototype("GrassTile", 1, new Sprite("grass00.png", kGrassSource));

		// Character prototype
		createCharacterPrototype("Guy", 1, new Sprite("Ukko.png", kCharacterSource));

		// Pickable item prototypes
		createPickableItemPrototype("Item_Wheat", 1, new Sprite("plants.png", kPlantItemSource));
		return true;
	}

#pragma region GroundEntity
	void createGroundEntityPrototype(
		const std::string & pName, const float pMovSpeed, // Entity stuff
		Sprite* pSprite)
	{
		int id = getNextId();
		SpriteManager::createSprite(id, pSprite);
		groundEntityPrototypes[id] = std::unique_ptr<GroundEntity>(
			GroundEntity::createPrototype(id, pMovSpeed)
			);
		idsByName[pName] = id;
	}

	GroundEntity* getGroundEntityPrototypeByName(const std::string & pName)
	{
		return getGroundEntityPrototypeById(idsByName[pName]);
	}

	GroundEntity* getGroundEntityPrototypeById(const int pId)
	{
		return groundEntityPrototypes.at(pId).get();
	}
#pragma endregion

#pragma region Pickable Item
	void createPickableItemPrototype(const std::string & pName, const int pMaxAmount, Sprite * pSprite)
	{
		int id = getNextId();
		SpriteManager::createSprite(id, pSprite);
		pickableItemPrototypes[id] = std::unique_ptr<PickableItem>(
			PickableItem::createPrototype(id, pMaxAmount)
			);
		idsByName[pName] = id;
	}

	PickableItem * getPickableItemPrototypeByName(const std::string & pName)
	{
		return getPickableItemPrototypeById(idsByName[pName]);
	}

	PickableItem * getPickableItemPrototypeById(const int pId)
	{
		return pickableItemPrototypes.at(pId).get();
	}
#pragma endregion

#pragma region Tile
	void createTilePrototype(const std::string & pName, const float pMovSpeed, Sprite * pSprite)
	{
		int id = getNextId();
		SpriteManager::createSprite(id, pSprite);
		tilePrototypes[id] = std::unique_ptr<Tile>(
			Tile::createPrototype(id, TileType::GRASS)
			);
		idsByName[pName] = id;
	}

	Tile * getTilePrototypeByName(const std::string & pName)
	{
		return getTilePrototypeById(idsByName[pName]);
	}

	Tile * getTilePrototypeById(const int pId)
	{
		return tilePrototypes.at(pId).get();
	}
#pragma endregion

#pragma region Character
	void createCharacterPrototype(const std::string & pName, const float pMovSpeed, Sprite * pSprite)
	{
		int id = getNextId();
		SpriteManager::createSprite(id, pSprite);
		characterPrototypes[id] = std::unique_ptr<Character>(
			Character::createPrototype(id)
			);
		idsByName[pName] = id;
	}

	Character * getCharacterPrototypeByName(const std::string & pName)
	{
		return characterPrototypes[getIdByName(pName)].get();
	}

	Character * getCharacterPrototypeById(const int pId)
	{
		return characterPrototypes[pId].get();
	}
#pragma endregion

	int getIdByName(const std::string & pName)
	{
		return idsByName[pName];
	}

	int getNextId()
	{
		return idCount++;
	}
}
