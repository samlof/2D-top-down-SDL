#include "Prototypes.h"

#include <map>

#include "SpriteManager.h"
#include "GroundEntity.h"
#include "Rectangle.h"
#include "units.h"
#include "GroundEntityPlantModule.h"
#include "Sprite.h"

namespace Prototypes {
	namespace {
		std::map<int, std::shared_ptr<GroundEntity> > groundEntityPrototypes;
		std::map<std::string, int> groundEntityPrototypesByName;

		// constants
		const Rectangle kWallSource(224, 384, 32, 32);
		const Rectangle kDoorSource(0, 0, 32, 32);
		const Rectangle kPlantSource(units::kTileSize * 6, 0, units::kTileSize, 64);


	}

	bool createPrototypes() {
		createPrototype("Door", 1, new Sprite("bad_door.png", kDoorSource));
		createPrototype("Wall", 0, new Sprite("walls1.png", kWallSource));
		createPrototype("Plant", 1, new Sprite("plants.png", kPlantSource));
		getPrototypeByName("Plant")->mModule = std::make_unique<GroundEntityPlantModule>(
			*getPrototypeByName("Plant").get()
			);


		SpriteManager::setGroundEntityFunction(getNextId() - 1,
			[](GroundEntity* pGrEntity) {
			int growth = static_cast<GroundEntityPlantModule*>(pGrEntity->mModule.get())->getGrowth();
			Rectangle newRect = kPlantSource;
			newRect.addY((growth - 1) * 64);
			return newRect;
		});


		SpriteManager::initSprites();
		return true;
	}

	void createPrototype(
		const std::string & pName, const float pMovSpeed, // Entity stuff
		Sprite* pSprite)
	{
		int id = getNextId();
		SpriteManager::createGroundEntitySprite(id, pSprite);
		groundEntityPrototypes[id] = std::make_shared<GroundEntity>(id, pMovSpeed);
		groundEntityPrototypesByName[pName] = id;
	}

	std::shared_ptr<GroundEntity> getPrototypeByName(const std::string & pName)
	{
		return getPrototypeById(groundEntityPrototypesByName[pName]);
	}

	int getPrototypeIdByName(const std::string & pName)
	{
		return groundEntityPrototypesByName[pName];
	}

	std::shared_ptr<GroundEntity> getPrototypeById(const int id)
	{
		return groundEntityPrototypes[id];
	}

	int getNextId()
	{
		return static_cast<int>(groundEntityPrototypes.size());
	}
}
