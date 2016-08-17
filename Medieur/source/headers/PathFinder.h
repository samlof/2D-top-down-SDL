#pragma once

#include <stack>

class Point;
class World;
class Tile;
class InventoryItem;

namespace PathFinder {
	void setWorld(World* pWorld);
	std::stack<Tile*> FindPath(Tile* pStartTile, Tile* pEndTile);
	std::stack<Tile*> FindPathForInventoryWith(Tile* pStartTile, InventoryItem* pItem, bool canTakeFromStockpile);
}