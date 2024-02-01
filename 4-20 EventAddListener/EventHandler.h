#pragma once

#include <queue>
#include <unordered_map>
#include <functional>
#include "../4-30 RecycleSystem/RecycleSystem.h"

using namespace std;




//�¼�����
template <typename... Args>
class EventArgs
{
public:
	//��ģ�����ֱ�ӽ�������װ���ṹ��,������ʹ��tuple�Ķ��⸴���ԡ� 
	//tuple<Args...> args;
	//EventArgs(Args... args) : args(args...) {}

	tuple<reference_wrapper<Args>...> args;
	EventArgs(Args&... args) : args(std::ref(args)...) {}

};


//�¼�����
template <typename... Args>
class EventHandler
{

public:
	//using Action = function<void(EventArgs<Args...>&)>; //ʹ�ú�����װ����������Ͳ�ƥ�������

	using Action = void(*)(EventArgs<Args...>&);


	//����¼�
	int AddListener(const Action& action)
	{
		int id = intRecycleSystem.Get();
		listeners.insert(pair<int, Action>(id, action));
		return id;
	};


	//�Ƴ��¼�
	void RemoveListener(int id)
	{
		auto item = listeners.find(id);
		if (item != listeners.end())
		{
			listeners.erase(item);
			intRecycleSystem.Recycle(id);
		}
	}

	//����
	void Invoke(EventArgs<Args...>& eventArgs)
	{
		for (auto& listener : listeners) {
			(*listener.second)(eventArgs);
		}
	}

	//����
	void Invoke(Args&... args)
	{
		EventArgs<Args...> eventArgs(args...);
		for (auto& listener : listeners) {
			(*listener.second)(eventArgs);
		}		
	}

	//����
	void operator()(EventArgs<Args...>& eventArgs)
	{
		Invoke(eventArgs);
	}

	//����
	void operator()(Args&... args)
	{
		Invoke(args...);
	}

	//����Ψһ���¼�  ���������ԭ�����¼�
	void operator=(const Action& action)
	{
		listeners.clear();
		intRecycleSystem.clear();
		AddListener(action);
	}

private:
	unordered_map<int, Action> listeners;//����ӳ��Ĳ���Ч�ʸ���,���������¼��ɷ������ܡ�

	IntRecycleSystem intRecycleSystem;
};
