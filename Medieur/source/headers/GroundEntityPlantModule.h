#pragma once

#include "IGroundEntityModule.h"
#include "CountdownCounter.h"

class GroundEntity;

class GroundEntityPlantModule : public IGroundEntityModule {
public:
	GroundEntityPlantModule(GroundEntity & pThisEntity);
	// Inherited via IGroundEntityModule
	virtual void update() override;
	virtual void interact() override;
	virtual void pickup() override;
	virtual GroundEntityPlantModule* clone(GroundEntity & pThisEntity) override { return new GroundEntityPlantModule(pThisEntity); }
	int getGrowth() const { return mGrowth; }

private:
	int mGrowth;
	int mHealth;
	CountdownCounter mGrowthCounter;
	CountdownCounter mHealthCounter;

	void rot();
};