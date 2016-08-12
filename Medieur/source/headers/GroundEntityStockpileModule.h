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
	virtual void interact(Character * pCharacter) override;
	virtual void pickup(Character * pCharacter) override;
	virtual GroundEntityStockpileModule * clone(IGroundEntityModule * pPrototype, GroundEntity * pThisEntity) override {
		return new GroundEntityStockpileModule(static_cast<GroundEntityStockpileModule*>(pPrototype), pThisEntity);
	}

private:
	GroundEntityStockpileModule(GroundEntityStockpileModule* pPrototype, GroundEntity * pThisEntity);
	GroundEntityStockpileModule(const int pDropItemId);

	void createJob();

	std::vector<int> mItems;
public:
	static GroundEntityStockpileModule* createPrototype(const int pDropItemId) {
		return new GroundEntityStockpileModule(pDropItemId);
	}
};

