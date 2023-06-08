// 1-03 Map.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>

//改map  无排序
//key 唯一标识，不可重复
template <typename KeyType, typename ValueType>
class Map
{
public:
	Map() :_node_head(nullptr) {}
	~Map() { clear(); }

	//插入到末尾
	void insert(KeyType key, ValueType value)
	{
		//第一次添加
		if (_node_head == nullptr)
		{
			_node_head = new Node(key, value);
			return;
		}

		//检查key是否存在
		Node* node = get_node(key);
		if (node == nullptr)
		{
			//key不存在 从末尾进行添加			
			node = new Node(key, value);
			get_end_node()->next = node;
			return;
		}

		//key存在
		throw std::runtime_error("key already exist");
	}

	//根据key进行删除
	void erase(KeyType key)
	{
		//检查key是否存在
		Node* node = get_node(key);
		if (node == nullptr)
		{
			throw std::runtime_error("key is null");
		}

		//删除头
		if (node->key == _node_head->key)
		{			
			Node* next_node = _node_head->next;
			delete _node_head;
			_node_head = next_node;
			return;
		}

		//删除尾部
		if (node->next == nullptr)
		{
			delete node;
			return;
		}

		//中间部分
		Node* last_node = get_last_node(node);
		last_node->next = node->next;
		delete node;


	}

	ValueType& operator[](KeyType key)
	{
		return get_Value(key);
	}


	void clear()
	{
		if (_node_head != nullptr)
		{
			Node* next_node = _node_head->next;
			delete _node_head;

			while (next_node != nullptr)
			{
				//后面还有节点  临时使用head记录该地址
				_node_head = next_node;
				next_node = next_node->next;
				delete _node_head;
			}
		}
	}


	void log()
	{
		if (_node_head != nullptr)
		{
			Node* node = _node_head;
			std::cout << "key:" << node->key << "	" << "value" << node->value << std::endl;

			while (node->next != nullptr)
			{
				node = node->next;
				std::cout << "key:" << node->key << "	" << "value" << node->value << std::endl;
			}
		}
	}

private:

	struct Node
	{
		KeyType key;
		ValueType value;
		Node* next;

		Node(const KeyType& k, const ValueType& v) :key(k), value(v), next(nullptr) {}
	};

	Node* _node_head;//节点头

	ValueType& get_Value(KeyType key)
	{
		Node* node = get_node(key);

		if (node == nullptr)
		{
			//为空的话
			throw std::runtime_error("not key");
		}

		return node->value;
	}


	//通过key获取Node
	Node* get_node(KeyType key)
	{
		return get_node(_node_head, key);
	}

	//递归获取node
	Node* get_node(Node* node, KeyType key)
	{
		if (node->key == key)
		{
			return node;
		}

		if (node->next != nullptr)
		{
			get_node(node->next, key);
		}
		else
		{
			//没有获取到
			return nullptr;
		}

	}

	//获取尾部节点
	Node* get_end_node()
	{
		Node* node = _node_head;

		while (node != nullptr && node->next != nullptr)
		{
			node = node->next;
		}

		return node;
	}


	//获取当前节点的上一个节点
	Node* get_last_node(Node* node)
	{
		if (node == _node_head)
		{
			return nullptr;
		}

		Node* temp_node = _node_head;

		while ( temp_node !=nullptr && temp_node->next != node)
		{
			temp_node = temp_node->next;
		}

		if (temp_node == nullptr)
			//无效的node
			throw std::runtime_error("invalid node");
		else
			return temp_node;
		
	}
		
};


class MyClass
{
public:
	MyClass() {};
	~MyClass() {};

	bool operator==(MyClass& c)
	{
		return sizeof(this) == sizeof(c) ? 0 : 1;
	}

private:

};


int main()
{
	{
		Map<int, int> map;

		for (size_t i = 0; i < 100; i++)
		{
			map.insert(i, i);
		}

		for (size_t i = 0; i < 100; i++)
		{
			if (i % 2 == 0)
			{
				map.erase(i);
			}
		}

		map.log();

	}


	{
		//自定义类型需要重载相关运算符
		Map<MyClass, int> map;
		
		for (size_t i = 0; i < 100; i++)
		{
			MyClass c;
			map.insert(c, i);
		}

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
