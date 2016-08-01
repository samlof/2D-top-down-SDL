#include "SpriteManager.h"

#include <unordered_map>
#include <string>
#include <functional>
#include <memory>

#include "Sprite.h"
#include "Tile.h"
#include "Rectangle.h"
#include "Character.h"
#include "World.h"
#include "Prototypes.h"
#include "GroundEntityPlantModule.h"
#include "GroundEntity.h"

namespace SpriteManager {

	namespace {
		using TileMap = std::unordered_map<TileType, std::unique_ptr<Sprite> >;
		TileMap tileSprites;
		using GroundEntityMap = std::unordered_map<int, std::unique_ptr<Sprite> >;
		GroundEntityMap groundEntitySprites;
		using CharacterMap = std::unordered_map<int, std::unique_ptr<Sprite> >;
		CharacterMap characterSprites;


		using GroundEntityFunctionMap = std::unordered_map<int, std::function<Rectangle(GroundEntity*)> >;
		GroundEntityFunctionMap groundEntityFunctions;



		const Rectangle kGrassSource(0, 0, 512, 512);
		const Rectangle kCharacterSource(0, 0, 32, 32);
	}

	void initSprites()
	{
		tileSprites.insert(TileMap::value_type(TileType::GRASS, std::make_unique<Sprite>("grass00.png", kGrassSource)));
		
		characterSprites.insert(CharacterMap::value_type(1, std::make_unique<Sprite>("Ukko.png", kCharacterSource)));
	}

	void createGroundEntitySprite(const int pId, Sprite* pSprite)
	{
		groundEntitySprites.insert(GroundEntityMap::value_type(
			pId, std::unique_ptr<Sprite>(pSprite)));
	}

	void setGroundEntityFunction(const int pId, std::function<Rectangle(GroundEntity*)> pFunction)
	{
		groundEntityFunctions[pId] = pFunction;
	}

	std::function<Rectangle(GroundEntity*)> getEntityFunction(const int pId)
	{
		return groundEntityFunctions[pId];
	}

	bool hasEntityFunction(const int pId)
	{
		return groundEntityFunctions.count(pId) == 1;
	}



	Sprite * getTileSprite(const Tile & pTile)
	{
		return tileSprites.at(pTile.getTileType()).get();
	}

	Sprite * getGroundEntitySpriteByName(const std::string & pFurnName)
	{
		return getGroundEntitySpriteById(Prototypes::getPrototypeIdByName(pFurnName));
	}

	Sprite * getGroundEntitySpriteById(const unsigned int pId)
	{
		return groundEntitySprites.at(pId).get();
	}

	Sprite * getCharacterSprite(std::shared_ptr<Character> pCharacter)
	{
		return characterSprites.at(1).get();
	}
}