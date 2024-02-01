#pragma once
#include "DynamicFactory.h"
#include <vector>
class DynamicManager
{
public:

	static DynamicManager& Instance()
	{
		static DynamicManager mgr;
		return mgr;
	}

	~DynamicManager() {};

private:
	DynamicManager() 
	{
		dynamics = DynamicFactory::Instance().Create<DynamicObject>();

		for (auto item: dynamics)
		{
			item->Init();
		}

		for (auto item : dynamics)
		{
			item->Start();
		}
	};

	std::vector<DynamicObject*> dynamics;
};

