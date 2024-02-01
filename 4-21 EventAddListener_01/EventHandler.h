#pragma once

#include <queue>
#include <unordered_map>
#include <functional>

#include "../4-30 RecycleSystem/RecycleSystem.h";

using namespace std;


//�¼�����
class EventArgs
{
public:
	virtual ~EventArgs() {}
};


//�¼�����
template <typename T , class = typename std::enable_if<std::is_base_of<EventArgs, T>::value>::type>
class EventHandler
{
	static_assert(std::is_base_of<EventArgs, T>::value, "T must be derived from EventArgs");// ���� T ������ EventArgs ����������
public:

	using Action = void(*)(T*);

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
	void Invoke(T* eventArgs)
	{
		for (auto& listener : listeners) {
			(*listener.second)(eventArgs);
		}
	}


	//����
	void operator()(T* eventArgs)
	{
		Invoke(eventArgs);
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
