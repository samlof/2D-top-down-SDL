#pragma once

#include <memory>
#include <string>

class GroundEntity;
class Sprite;

namespace Prototypes {
	bool createPrototypes();
	void createPrototype(const std::string & pName, const float pMovSpeed, Sprite* pSprite);

	std::shared_ptr<GroundEntity> getPrototypeByName(const std::string& pName);
	int getPrototypeIdByName(const std::string& pName);
	std::shared_ptr<GroundEntity> getPrototypeById(const int id);
	int getNextId();
}