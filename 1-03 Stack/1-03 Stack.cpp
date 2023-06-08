// 1-03 Stack.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <string>
#include <sstream>


//先进后出，后进先出
//入栈放在最前面,出栈也从最前面开始
template <typename T>
class Stack
{
public:
	Stack() :top(nullptr) {};
	~Stack() { clear(); };

	/// <summary>
	/// 插入元素到栈顶
	/// </summary>
	/// <param name="val">数据</param>
	void push(T val)
	{
		Node* temp_node = new Node(val);
		if (top == nullptr)
		{
			top = temp_node;
			return;
		}
		//直接设置temp_node->next = top
		temp_node->next = top;
		//更新top
		top = temp_node;
	}

	/// <summary>
	/// 将元素从栈中弹出，并释放对应的内存
	/// </summary>
	/// <returns>返回该节点的数据</returns>
	T pop()
	{
		if (top == nullptr) return T();
		//暂存top
		Node* temp_node = top;
		//直接更新top
		top = temp_node->next;

		//缓存temp_node->data，以便进行返回
		T temp_data = temp_node->data;
		delete temp_node;
		return temp_data;
	}

	/// <summary>
	/// 查看栈顶元素
	/// </summary>
	/// <returns>返回栈顶中的元素</returns>
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
		while (temp_node != nullptr)
		{
			count++;
			temp_node = temp_node->next;
		}
		return count;
	}

	void clear()
	{
		Node* temp_node = top;
		while (temp_node != nullptr)
		{
			temp_node = top->next;
			delete top;
			top = temp_node;
		}
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

	Node* top;//栈顶指针

};

int main()
{

	Stack<char> stack;

	for (size_t i = 97; i < 107; i++)
	{
		stack.push(i);
	}

	stack.log();

	stack.pop();
	stack.pop();
	stack.pop();
	stack.pop();
	stack.pop();
	stack.log();

	stack.clear();
	for (size_t i = 97; i < 107; i++)
	{
		stack.push(i);
	}
	stack.log();

	std::cout << "size:" << stack.size() << "	" << "peek:" << stack.peek();
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
