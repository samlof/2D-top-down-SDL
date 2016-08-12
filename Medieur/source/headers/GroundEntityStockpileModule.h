#pragma once

#include "IGroundEntityModule.h"

#include <vector>

class GroundEntity;
class Job;

class GroundEntityStockpileModule : public IGroundEntityModule
{
public:
	~GroundEntityStockpileModule();

	void addItem(int pId) { mItems.push_back(pId); }
	// Inherited via IGroundEntityModule
	virtual void update() override;
	virtual void interact() override {}
	virtual void pickup() override {}
	virtual GroundEntityStockpileModule * clone(IGroundEntityModule * pPrototype, GroundEntity * pThisEntity) override {
		return new GroundEntityStockpileModule(static_cast<GroundEntityStockpileModule*>(pPrototype), pThisEntity);
	}

private:
	GroundEntityStockpileModule(GroundEntityStockpileModule* pPrototype, GroundEntity * pThisEntity);
	GroundEntityStockpileModule();

	std::vector<int> mItems;
	Job* mJob;

	void createJob();
	void stockChanged();
public:
	static GroundEntityStockpileModule* createPrototype() {
		return new GroundEntityStockpileModule();
	}
};

