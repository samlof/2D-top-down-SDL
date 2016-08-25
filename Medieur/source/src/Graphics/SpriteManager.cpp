#include "Graphics\SpriteManager.h"

#include <unordered_map>
#include <string>
#include <functional>
#include <memory>

#include "Graphics\Sprite.h"

#include "Tile.h"
#include "Rectangle.h"
#include "Character.h"
#include "World.h"
#include "Prototypes.h"
#include "GroundEntityPlantModule.h"
#include "GroundEntity.h"

namespace SpriteManager {

	namespace {
		using SpriteMap = std::unordered_map<int, std::unique_ptr<Sprite> >;
		SpriteMap spriteMap;

		using GroundEntitySpriteFunctionMap = std::unordered_map<int, std::function<Rectangle(GroundEntity*)> >;
		GroundEntitySpriteFunctionMap groundEntitySpriteFunctions;
	}

	void createSprite(const int pId, Sprite* pSprite)
	{
		spriteMap[pId] = std::unique_ptr<Sprite>(pSprite);
	}

	void clearAll()
	{
		spriteMap.clear();
		groundEntitySpriteFunctions.clear();
	}

	void setGroundEntityFunction(const int pId, std::function<Rectangle(GroundEntity*)> pFunction)
	{
		groundEntitySpriteFunctions[pId] = pFunction;
	}

	bool hasGroundEntityFunction(const int pId)
	{
		return groundEntitySpriteFunctions.count(pId) == 1;
	}

	std::function<Rectangle(GroundEntity*)> getEntityFunction(const int pId)
	{
		return groundEntitySpriteFunctions.at(pId);
	}

	Sprite * getSpriteByName(const std::string & pFurnName)
	{
		return getSpriteById(Prototypes::getIdByName(pFurnName));
	}

	Sprite * getSpriteById(const unsigned int pId)
	{
		return spriteMap.at(pId).get();
	}
}