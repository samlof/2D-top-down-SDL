#pragma once

class GroundEntity;

class IGroundEntityModule {
public:
	IGroundEntityModule(GroundEntity* pThisEntity) : mThisEntity(pThisEntity) {}

	virtual void update() = 0;
	virtual void interact() = 0;
	virtual void pickup() = 0;
	virtual ~IGroundEntityModule() {}
	GroundEntity* getEntity() { return mThisEntity; }

	virtual IGroundEntityModule* clone(IGroundEntityModule* pPrototype, GroundEntity * pThisEntity) = 0;
protected:
	GroundEntity * mThisEntity;
};