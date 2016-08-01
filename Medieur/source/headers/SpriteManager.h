#pragma once

#include <string>
#include <memory>
#include <functional>

#include "Rectangle.h"

class Sprite;
class Tile;
class GroundEntity;
class Character;

namespace SpriteManager {
	void initSprites();
	void createGroundEntitySprite(const int pId, Sprite* pSprite);

	void setGroundEntityFunction(const int pId, std::function<Rectangle(GroundEntity*)> pFunction);
	std::function<Rectangle(GroundEntity*)> getEntityFunction(const int pId);
	bool hasEntityFunction(const int pId);

	Sprite* getTileSprite(const Tile & pTile);
	Sprite* getGroundEntitySpriteByName(const std::string & pFurnName);
	Sprite* getGroundEntitySpriteById(const unsigned int pId);
	Sprite* getCharacterSprite(std::shared_ptr<Character> pCharacter);
}