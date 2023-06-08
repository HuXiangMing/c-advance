// 1-04 Queue.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <string>
#include <sstream>

//先进先出，后进后出
//入队放在最后面，出队从最前面开始

template <typename T>
class Queue
{
public:
	Queue() :top(nullptr),tail(nullptr) {};
	~Queue() { clear(); };



	void push(T val)
	{
		Node* temp_node = new Node(val);
		if (top == nullptr)
		{
			top = temp_node; tail = temp_node; return;
		}

		//获取到结尾的元素进行设置
		tail->next = temp_node;
		tail = temp_node;
	}



	T pop()
	{
		if (top == nullptr)
		{
			return T();
		}

		Node* temp_node = top;
		top = top->next;
		if (top == nullptr) tail = nullptr;
		delete temp_node;
	}

	T peek()
	{
		if (top == nullptr)
		{
			return T();
		}

		return top->data;

	}


	size_t size()
	{	
		size_t count = 0;
		Node* temp_node = top;
		if (top == nullptr) return 0;
		while (temp_node != tail)
		{
			temp_node = temp_node->next;
			count++;
		}
		return count + 1;
	}

	void clear()
	{
		if (top == nullptr) return;

		while (top!=tail)
		{
			Node* temp_node = top;
			top = top->next;
			delete temp_node;
		}

		if(top!=nullptr) delete top;
		top = nullptr; tail = nullptr;
	}
		


	void log()
	{
		//因为栈尾部的元素的next为nullptr,所以可以使用死循环进行打印
		Node* temp_node = top;

		std::stringstream ss;
		while (temp_node != nullptr)
		{
			ss << temp_node->data << " ";
			temp_node = temp_node->next;
		}

		std::cout << ss.str() << std::endl;
	}

private:
	struct Node
	{
		T data;
		Node* next;
		Node(T val) :data(val), next(nullptr) {}
	};

	Node* top;//队顶指针
	Node* tail;//尾部指针，因为每次push元素都需要查找到尾部元素，所以我们这里直接将尾部元素进行缓存，以push提高效率
};



int main()
{
	Queue<char> queue;

	for (size_t i = 97; i < 107; i++)
	{
		queue.push(i);
	}

	queue.log();

	queue.pop();
	queue.pop();
	queue.pop();
	queue.pop();
	queue.pop();
	queue.log();

	queue.clear();
	for (size_t i = 97; i < 107; i++)
	{
		queue.push(i);
	}
	queue.log();

	std::cout << "size:" << queue.size() << "	" << "peek:" << queue.peek();
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
