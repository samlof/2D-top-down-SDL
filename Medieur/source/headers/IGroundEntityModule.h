#pragma once

class GroundEntity;

class IGroundEntityModule {
public:
	IGroundEntityModule(GroundEntity& pThisEntity) : mThisEntity(pThisEntity) {}
	IGroundEntityModule(IGroundEntityModule* pProto, GroundEntity& pThisEntity) : mThisEntity(pThisEntity) {}

	virtual void update() = 0;
	virtual void interact() = 0;
	virtual void pickup() = 0;
	virtual ~IGroundEntityModule() {}

	virtual IGroundEntityModule* clone(GroundEntity & pThisEntity) = 0;
protected:
	GroundEntity & mThisEntity;
};