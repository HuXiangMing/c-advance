// 4-03 EventAddListener.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
// 一个事件管理器EventHandler  与  事件参数 EventArgs  
// 使用AddListener 添加事件
// 使用Invoke 触发事件
// 参数以引用的方式传递
// 
// 缺陷：暂不支持继承传递参数（EventArgs的子类）

#include <iostream>
#include "EventHandler.h"
int main()
{
	std::cout << "--- (调用时传递变量)---" << endl;
	{
		//准备一个 事件 EventHandler
		EventHandler<string, string> handler;

		//添加事件
		int actionid = handler.AddListener([](EventArgs<string, string>& args)->void {
			std::cout << "action1调用" << endl;
			get<0>(args.args).get() = "11";
			get<1>(args.args).get() = "111";
			});

		int actionid1 = handler.AddListener([](EventArgs<string, string>& args)->void {
			//...
			std::cout << "action2调用" << endl;
			get<0>(args.args).get() = "22";
			get<1>(args.args).get() = "222";
			});

		//移除 actionid1
		handler.RemoveListener(actionid);


		string s1 = "100"; string s2 = "200";
		handler(s1, s2); //改变了s1 s2的值
		cout << s1 << endl; cout << s2 << endl;

	}

	std::cout << "---（调用时传递 EventArgs）---" << endl;
	{
		//准备一个 事件 EventHandler
		EventHandler<string, string> handler;
		//添加事件
		int actionid = handler.AddListener([](EventArgs<string, string>& args)->void {
			std::cout << "action1调用" << endl;
			get<0>(args.args).get() = "11";
			get<1>(args.args).get() = "111";
			});
		string s1 = "100"; string s2 = "200";
		EventArgs<string, string> args(s1, s2);
		handler.Invoke(args);
		cout << s1 << endl; cout << s2 << endl;
	}
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
