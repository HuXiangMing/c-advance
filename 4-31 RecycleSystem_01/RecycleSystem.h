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
		//队列中无可用的item 创建
		if (recycledItems.size() <= 0)
		{
			next = CreatItem();
			usedItems.insert(next);
			return next;
		}

		//取得队列最前方的元素 移除
		T item = recycledItems.front();
		recycledItems.pop();
		return item;
	}

	//回收
	void Recycle(T& item)
	{
		if (usedItems.count(item))
		{
			recycledItems.push(item);
			usedItems.erase(item);
		}
	}

	//清空
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

	std::queue<T> recycledItems;//可用列表
	std::unordered_set<T> usedItems; // 正在使用的列表
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

