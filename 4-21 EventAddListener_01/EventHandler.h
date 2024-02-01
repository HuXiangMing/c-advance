#pragma once

#include <queue>
#include <unordered_map>
#include <functional>

#include "../4-30 RecycleSystem/RecycleSystem.h";

using namespace std;


//事件参数
class EventArgs
{
public:
	virtual ~EventArgs() {}
};


//事件基类
template <typename T , class = typename std::enable_if<std::is_base_of<EventArgs, T>::value>::type>
class EventHandler
{
	static_assert(std::is_base_of<EventArgs, T>::value, "T must be derived from EventArgs");// 限制 T 必须是 EventArgs 或其派生类
public:

	using Action = void(*)(T*);

	//添加事件
	int AddListener(const Action& action)
	{
		int id = intRecycleSystem.Get();
		listeners.insert(pair<int, Action>(id, action));
		return id;
	};


	//移除事件
	void RemoveListener(int id)
	{
		auto item = listeners.find(id);
		if (item != listeners.end())
		{
			listeners.erase(item);
			intRecycleSystem.Recycle(id);
		}
	}

	//调用
	void Invoke(T* eventArgs)
	{
		for (auto& listener : listeners) {
			(*listener.second)(eventArgs);
		}
	}


	//调用
	void operator()(T* eventArgs)
	{
		Invoke(eventArgs);
	}


	//设置唯一的事件  会清楚所有原来的事件
	void operator=(const Action& action)
	{
		listeners.clear();
		intRecycleSystem.clear();
		AddListener(action);
	}

private:
	unordered_map<int, Action> listeners;//无序映射的查找效率更高,可以提升事件派发的性能。

	IntRecycleSystem intRecycleSystem;
};
