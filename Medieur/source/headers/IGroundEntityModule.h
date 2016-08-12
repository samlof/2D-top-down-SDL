#pragma once

class GroundEntity;
class Character;

class IGroundEntityModule {
public:

	virtual void update() = 0;
	virtual void interact(Character* pCharacter) = 0;
	virtual void pickup(Character* pCharacter) = 0;
	virtual ~IGroundEntityModule() {}
	GroundEntity* getEntity() { return mThisEntity; }

	virtual IGroundEntityModule* clone(IGroundEntityModule* pPrototype, GroundEntity * pThisEntity) = 0;
protected:
	GroundEntity * mThisEntity;

	IGroundEntityModule(GroundEntity* pThisEntity) : mThisEntity(pThisEntity) {}

};