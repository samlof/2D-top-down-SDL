#pragma once

enum class ItemType {
	FOOD,
	TOOL,
	JOY
};

class PickableItem {
public:
	PickableItem(const int pId) : mId(pId) {}

private:
	const int mId;
};