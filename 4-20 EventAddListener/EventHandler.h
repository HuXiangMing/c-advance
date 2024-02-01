#pragma once

#include <queue>
#include <unordered_map>
#include <functional>
#include "../4-30 RecycleSystem/RecycleSystem.h"

using namespace std;




//事件参数
template <typename... Args>
class EventArgs
{
public:
	//参模板可以直接将参数包装进结构体,避免了使用tuple的额外复杂性。 
	//tuple<Args...> args;
	//EventArgs(Args... args) : args(args...) {}

	tuple<reference_wrapper<Args>...> args;
	EventArgs(Args&... args) : args(std::ref(args)...) {}

};


//事件基类
template <typename... Args>
class EventHandler
{

public:
	//using Action = function<void(EventArgs<Args...>&)>; //使用函数包装器会出现类型不匹配的问题

	using Action = void(*)(EventArgs<Args...>&);


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
	void Invoke(EventArgs<Args...>& eventArgs)
	{
		for (auto& listener : listeners) {
			(*listener.second)(eventArgs);
		}
	}

	//调用
	void Invoke(Args&... args)
	{
		EventArgs<Args...> eventArgs(args...);
		for (auto& listener : listeners) {
			(*listener.second)(eventArgs);
		}		
	}

	//调用
	void operator()(EventArgs<Args...>& eventArgs)
	{
		Invoke(eventArgs);
	}

	//调用
	void operator()(Args&... args)
	{
		Invoke(args...);
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
