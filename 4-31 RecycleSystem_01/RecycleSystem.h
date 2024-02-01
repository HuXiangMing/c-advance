#pragma once
#include <iostream>
#include <queue>
#include <unordered_set>
#include <typeindex>
#include <map>
#include <string>

template <typename T>
class RecycleSystem
{
public:

	using GetItemHander = T(*)();

	RecycleSystem(T t) :next(t) {}

	virtual T Get()
	{
		//�������޿��õ�item ����
		if (recycledItems.size() <= 0)
		{
			next = CreatItem();
			usedItems.insert(next);
			return next;
		}

		//ȡ�ö�����ǰ����Ԫ�� �Ƴ�
		T item = recycledItems.front();
		recycledItems.pop();
		return item;
	}

	//����
	void Recycle(T& item)
	{
		if (usedItems.count(item))
		{
			recycledItems.push(item);
			usedItems.erase(item);
		}
	}

	//���
	void Clear()
	{
		while (!recycledItems.empty)
		{
			recycledItems.pop();
		}
		usedItems.clear();
	}


	GetItemHander GetItem;

protected:

	virtual T CreatItem()
	{
		if (GetItem != nullptr)
			return GetItem();
	};

	std::queue<T> recycledItems;//�����б�
	std::unordered_set<T> usedItems; // ����ʹ�õ��б�
	T next;
};

class IntRecycleSystem :public RecycleSystem<int>
{
public:
	IntRecycleSystem() :RecycleSystem(0) {}
private:
	int CreatItem() override { return ++next; }
};

class StringRecycleSystem :public RecycleSystem<std::string>
{
public:
	StringRecycleSystem() :RecycleSystem("HXM_0") {}
private:
	int id = 0;
	std::string str = "HXM_";
	std::string CreatItem()  override { return str + std::to_string(++id); }
};

