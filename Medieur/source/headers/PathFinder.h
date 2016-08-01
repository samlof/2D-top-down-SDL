#pragma once

#include <stack>

class Point;
class World;
class Tile;

namespace PathFinder {
	void setWorld(World* pWorld);
	std::stack<Tile*> FindPath(Tile* pStartTile, Tile* pEndTile);
}