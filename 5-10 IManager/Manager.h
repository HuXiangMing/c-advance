#pragma once
#include <unordered_map>

#include "../4-30 RecycleSystem/RecycleSystem.h"

//Լ���ӿ�
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

//����ʵ��
template <typename T, typename K = int>
class Manager:public IManager<T,K>
{
public:
	Manager() : IManager<T, K>() { }

	virtual K Add(T* t)
	{
		K k = recycleSystem->Get();
		this->dataMap[k] = t; //ģ�����ڼ̳л���ĳ�Աʱ����������ʱ�޷���ȷ�ؽ�����Щ��Ա����� this-> ���԰�����������ȷ���ҵ���Щ��Ա��
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
	RecycleSystem<K>* recycleSystem;//�����ำֵ������ʱ����Ĺ��캯����
	//virtual void SetRecycleSystem() = 0;
};

