#pragma once

#include <memory>
#include <string>

class GroundEntity;
class InventoryItem;
class Tile;
class Character;
namespace Graphics {
	class Sprite;
}

namespace Prototypes {
	bool createPrototypes();
	void clearAll();
	using Graphics::Sprite;
	void createGroundEntityPrototype(const std::string & pName, const float pMovSpeed, Sprite* pSprite);
	GroundEntity* getGroundEntityPrototypeByName(const std::string& pName);
	GroundEntity* getGroundEntityPrototypeById(const int pId);

	void createPickableItemPrototype(const std::string & pName, const int pMovSpeed, Sprite* pSprite);
	InventoryItem* getPickableItemPrototypeByName(const std::string& pName);
	InventoryItem* getPickableItemPrototypeById(const int pId);

	void createTilePrototype(const std::string & pName, const float pMovSpeed, Sprite* pSprite);
	Tile* getTilePrototypeByName(const std::string& pName);
	Tile* getTilePrototypeById(const int pId);

	void createCharacterPrototype(const std::string & pName, const float pMovSpeed, Sprite* pSprite);
	Character* getCharacterPrototypeByName(const std::string& pName);
	Character* getCharacterPrototypeById(const int pId);


	int getIdByName(const std::string& pName);
	int getNextId();
}