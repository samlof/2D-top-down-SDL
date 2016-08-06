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
	void createSprite(const int pId, Sprite* pSprite);

	void setGroundEntityFunction(const int pId, std::function<Rectangle(GroundEntity*)> pFunction);
	bool hasGroundEntityFunction(const int pId);
	std::function<Rectangle(GroundEntity*) > getEntityFunction(const int pId);

	Sprite* getSpriteByName(const std::string & pFurnName);
	Sprite* getSpriteById(const unsigned int pId);
}