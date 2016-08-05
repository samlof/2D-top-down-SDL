#pragma once

enum class ItemType {
	FOOD,
	TOOL,
	JOY
};

class Item {
public:
	Item(const int pId) : mId(pId) {}

private:
	const int mId;
};