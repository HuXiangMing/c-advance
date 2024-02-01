#pragma once
#include <unordered_map>

#include "../4-30 RecycleSystem/RecycleSystem.h"

//约定接口
template <typename T, typename K>
class IManager
{
	static_assert(std::is_class<T>::value, "T must be a class type.");
public:
	IManager() {};
	virtual K Add(T* t) = 0;
	virtual bool Remove(K k) = 0;
	virtual T* Get(K k) = 0;
protected:
	std::unordered_map<K, T*> dataMap;
	virtual ~IManager() {};
};

//初步实现
template <typename T, typename K = int>
class Manager:public IManager<T,K>
{
public:
	Manager() : IManager<T, K>() { }

	virtual K Add(T* t)
	{
		K k = recycleSystem->Get();
		this->dataMap[k] = t; //模板类在继承基类的成员时，编译器有时无法正确地解析这些成员。添加 this-> 可以帮助编译器正确地找到这些成员。
		return k;
	}

	virtual bool Remove(K k)
	{
		auto it = this->dataMap.find(k);
		if (it != this->dataMap.end())
		{
			this->dataMap.erase(it);
			return true;
		}
		return false;
	};

	virtual T* Get(K k)
	{
		auto it = this->dataMap.find(k);
		if (it != this->dataMap.end()) {
			return it->second;
		}
		return nullptr;
	};
protected:	
	RecycleSystem<K>* recycleSystem;//在子类赋值（可以时子类的构造函数）
	//virtual void SetRecycleSystem() = 0;
};

