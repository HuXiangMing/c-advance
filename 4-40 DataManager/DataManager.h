#pragma once
#include <unordered_map>
#include "../4-11 DynamicObject_01/DynamicObject.h"
#include "../4-11 DynamicObject_01/DynamicCreate.h"
#include "../4-11 DynamicObject_01/DynamicFactory.h"
#include "../4-30 RecycleSystem/RecycleSystem.h"
#include "../5-10 IManager/Manager.h"

class IntRecycleSystem;


class Data
{
public:
	Data() {};
	Data(int id, const std::string name) :id(id), name(name) {}
	int GetID() { return id; }
	std::string GetName() { return name; }
protected:
	int id;
	std::string name;
};

template<typename T>
class DynamicData:public Data,public DynamicCreate<T>
{

};



template <typename T = Data, typename K = int , class = typename std::enable_if<std::is_base_of<Data, T>::value>::type>
class DataManager :public Manager<T, K> {
	static_assert(std::is_base_of<Data, T>::value, "T must be derived from Data");// 限制 其派生类
public:
	DataManager() :Manager<T, K>()
	{
		Manager<T, K>::recycleSystem = new IntRecycleSystem();

		std::vector<DynamicObject*> datas = DynamicFactory::Instance().Create<DynamicObject>();

		for(DynamicObject* item : datas)
		{			
			T* data = dynamic_cast<T*>(item);
			Manager<T, K>::Add(data);
			item->Init();
			item->Start();
		}
	};
};
