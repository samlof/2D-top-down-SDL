#pragma once

#include "IGroundEntityModule.h"
#include "CountdownCounter.h"

class GroundEntity;
class Job;

class GroundEntityPlantModule : public IGroundEntityModule {
public:
	GroundEntityPlantModule(GroundEntityPlantModule* pPrototype, GroundEntity * pThisEntity);

	// Inherited via IGroundEntityModule
	virtual void update() override;
	virtual void interact(Character* pCharacter) override;
	virtual void pickup(Character* pCharacter) override;

	virtual GroundEntityPlantModule* clone(IGroundEntityModule* pPrototype, GroundEntity * pThisEntity) override {
		return new GroundEntityPlantModule(static_cast<GroundEntityPlantModule*>(pPrototype), pThisEntity);
	}
	int getGrowth() const { return mGrowth; }


private:
	int mGrowth;
	int mHealth;
	CountdownCounter mGrowthCounter;
	CountdownCounter mHealthCounter;
	Job* mInteractJob;
	Job* mPickupJob;

	int mDropItemId;
	void rot();

	GroundEntityPlantModule(const int pDropItemId);
public:
	static GroundEntityPlantModule* createPrototype(const int pDropItemId) {
		return new GroundEntityPlantModule(pDropItemId);
	}
};