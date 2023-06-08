// 1-02 List.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
// 使用链表实现的List

#include <iostream>
#include <chrono>

//插入、删除快，获取慢
//std::list 则是通过双向链表实现的。不支持快速随机访问。
//std::list 适用于需要频繁插入和删除元素的场景。
template <typename T>
class List
{
public:
	List() :_head(nullptr), _tail(nullptr), _size(0) {}
	~List() { clear(); }

	T& operator[](const size_t pos)
	{
		if (pos == 0) return _head->data;
		if (pos > 0 && pos < _size) return  get_node(pos)->data;
		return T();
	}

	/// <summary>
	/// 在链表的pos位置后面插入val
	/// </summary>
	/// <param name="val"></param>
	/// <param name="pos"></param>
	void insert(T val, size_t pos)
	{
		if (pos == 0)
		{
			push_front(val);  return;
		}

		if (pos == _size - 1)
		{
			push_back(val); return;
		}

		if (pos > 0 && pos < _size)
		{
			//获取pos位置节点
			Node* temp_node = get_node(pos);
			Node* node = new Node(val);
			node->next = temp_node->next;
			temp_node->next = node;
			_size++; return;
		}

		//格式错误
		throw std::out_of_range("pos out of range ");
	}


	/// <summary>
	/// 删除指定位置的节点
	/// </summary>
	/// <param name="pos"></param>
	void erase(size_t pos)
	{
		if (pos == 0)
		{
			pop_front(); return;
		}


		if (pos == _size - 1)
		{
			pop_back(); ; return;
		}

		if (pos > 0 && pos < _size)
		{
			//获取pos位置上一个节点
			Node* temp_last_node = get_node(pos - 1);
			Node* temp_node = temp_last_node->next;
			temp_last_node->next = temp_node->next;
			delete temp_node; _size--; return;
		}

		//格式错误
		throw std::out_of_range("pos out of range ");
	}

	/// <summary>
	/// 向链表末尾添加元素
	/// </summary>
	/// <param name="val"></param>
	void push_back(T val)
	{
		Node* node = new Node(val);
		//1.头节点为null的操作
		if (_head == nullptr)
		{
			_head = node, _tail = node; _size++; return;
		}

		//2.部位null添加到末尾
		Node* temp_node = _tail;
		temp_node->next = node;
		_tail = node; _size++;
	}


	/// <summary>
	/// 向链表头部添加元素
	/// </summary>
	/// <param name="val"></param>
	void push_front(T val)
	{
		Node* node = new Node(val);
		if (_head == nullptr)
		{
			_head = node, _tail = node; _size++; return;
		}
		Node* temp_node = _head;
		_head = node;
		_head->next = temp_node;
		_size++;
	}



	/// <summary>
	/// 移除链表的末端元素
	/// </summary>
	void pop_back()
	{
		if (_tail == nullptr) return;

		//只有一个元素
		if (_head == _tail)
		{
			delete _tail;
			_head = _tail = nullptr; _size--; return;
		}

		//获取末端节点的上一个节点
		Node* temp_node = get_node(size() - 2);

		//直接移除并释放相应内存
		delete _tail;
		_tail = temp_node;
		_size--;
	}

	/// <summary>
	/// 移除链表的头部元素
	/// </summary>
	void pop_front()
	{
		if (_head == nullptr) return;

		//只有一个元素
		if (_head == _tail)
		{
			delete _tail;
			_head = _tail = nullptr; _size--; return;
		}

		Node* temp_node = _head;
		_head = _head->next;
		delete temp_node;
		_size--;
	}



	void clear()
	{
		if (_head == nullptr)return;

		Node* temp_node = _head;

		while (_head != _tail)
		{
			temp_node = _head;
			_head = _head->next;
			delete temp_node;
		}

		delete _head;
		_head = _tail = nullptr; _size = 0;
	}


	size_t size()
	{
		//每次获取效率极其低下
		//if (_head == nullptr)return 0;
		//if (_head == _tail) return 1;
		//size_t count = 0;
		//Node* temp_node = _head;
		//while (temp_node != _tail)
		//{
		//	temp_node = temp_node->next;
		//	count++;
		//}
		//return count + 1;

		return _size;
	}


	void log()
	{
		Node* temp_node = _head;

		while (temp_node != _tail)
		{
			std::cout << temp_node->data << " ";
			temp_node = temp_node->next;
		}

		std::cout << temp_node->data << std::endl;
	}

private:
	struct Node
	{
		T data;
		Node* next;
		//引用传值避免拷贝
		Node(const T& val) :data(val), next(nullptr) {};
	};

	Node* _head;//节点头
	Node* _tail;//尾点头
	size_t _size;



	Node* get_node(size_t pos)
	{
		if (pos == 0) return _head;

		size_t index = 0;
		Node* temp_node = _head;
		while (index < pos)
		{
			temp_node = temp_node->next;
			index++;

			if (temp_node == nullptr)
			{
				//格式错误
				throw std::out_of_range("pos out of range ");
			}
		}

		return temp_node;
	}
};



int main()
{
	{
		List<int> list;

		for (size_t i = 0; i < 10; i++)
		{
			list.push_back(i);
			list.push_front(i);
		}
		list.log();

		for (size_t i = 0; i < 5; i++)
		{
			list.pop_back();
			list.pop_front();
		}

		list.log();
		std::cout << "size:" << list.size() << std::endl;


		for (size_t i = 0; i < 5; i++)
		{
			list.insert(i, 9);
			list.log();
		}

		for (size_t i = 0; i < 5; i++)
		{
			list.erase(i);
			list.log();
		}

	}

	//时间对比 插入
	{
		int i = 10000;
		List<int> list;

		// 获取当前时间点
		auto start = std::chrono::high_resolution_clock::now();

		while (i > 0)
		{
			//list.push_back(i);
			list.insert(list.size() / 2,0);//随机插入，还凑活
			i--;
		}
		//int a = vector[10000000-1];
		list.erase(0);

		// 获取结束时间点
		auto end = std::chrono::high_resolution_clock::now();
		// 计算时间差
		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
		// 输出计时结果
		std::cout << "Time elapsed: " << duration.count() << " microseconds." << std::endl;
		std::cout << "size:" << list.size() << std::endl;
	}

	std::cout << "Hello World!\n";
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
