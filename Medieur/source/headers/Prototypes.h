#pragma once

#include <memory>
#include <string>

class GroundEntity;
class PickableItem;
class Sprite;
class Tile;

namespace Prototypes {
	bool createPrototypes();

	void createGroundEntityPrototype(const std::string & pName, const float pMovSpeed, Sprite* pSprite);
	GroundEntity* getGroundEntityPrototypeByName(const std::string& pName);
	GroundEntity* getGroundEntityPrototypeById(const int id);

	void createPickableItemPrototype(const std::string & pName, const float pMovSpeed, Sprite* pSprite);
	PickableItem* getPickableItemPrototypeByName(const std::string& pName);
	PickableItem* getPickableItemPrototypeById(const int id);

	void createTilePrototype(const std::string & pName, const float pMovSpeed, Sprite* pSprite);
	Tile* getTilePrototypeByName(const std::string& pName);
	Tile* getTilePrototypeById(const int id);

	int getIdByName(const std::string& pName);
	int getNextId();
}