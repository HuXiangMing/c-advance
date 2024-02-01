// 4-04 EventAddListener_01.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "EventHandler.h"

class EventArgesA :public EventArgs
{
public:

    EventArgesA(int i, string str) :EventArgs(), i(i), str(str) {};
    int i;
    string str;
};

int main()
{
	std::cout << "--- (调用时传递变量)---" << endl;
	{
		//准备一个 事件 EventHandler
		EventHandler<EventArgesA> handler;

		//添加事件
		int actionid = handler.AddListener([](EventArgesA* args)->void {
			std::cout << "action1调用" << endl;
			args->i = 100;
			args->str = "str100";
			});

		shared_ptr<EventArgesA> argesA = make_shared<EventArgesA>(1, "str1");

		cout << argesA->i << endl; cout << argesA->str << endl;
		handler(argesA.get());
		cout << argesA->i << endl; cout << argesA->str << endl;
		

	}
	//EventHandler<int> handler;  //编译报错  不是EventArgs 类型

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
