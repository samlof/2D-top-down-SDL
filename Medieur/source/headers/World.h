#pragma once

#include <vector>
#include <memory>

#include "Point.h"

class Tile;
class Character;
class GroundEntity;

class World
{
public:
	// Statics
	static World* GenerateTestWorld();

	World(const unsigned int width, const unsigned int height);
	~World();

	Tile* getTile(const int pX, const int pY);

	size_t getWidth() const { return mTiles.size(); }
	size_t getHeight() const;

	void update();

	void createCharacter(int pX, int pY);
	void createGroundEntity(int pX, int pY, std::shared_ptr<GroundEntity> pPrototype);
private:
	std::vector<std::vector<Tile> > mTiles;
	std::vector<std::shared_ptr<Character> > mCharacters;
};