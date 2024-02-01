// 5-10 IManager.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
// 管理模块


#include <vector>

#include "Manager.h"

class A
{
public:
	A() {};
	int id = 0;
	~A();

private:

};

class AManager:public Manager<A>
{
public:
	AManager() : Manager<A>() 
	{
		recycleSystem = new IntRecycleSystem();
	}
};


#include <iostream>

int main()
{
	AManager aManager;
	//aManager.SetRecycleSystem();

	std::vector<int> vs;
	for (size_t i = 0; i < 5; i++)
	{
		A* a = new A();		
		a->id = i;
		int id = aManager.Add(a);
		vs.push_back(id);

		std::cout <<"id:"<<id<<"	"<<"address" << a << std::endl;
	}


	for (size_t i = 0; i < vs.size(); i++)
	{
		A* a = aManager.Get(vs[i]);

		std::cout << "id:" << vs[i] << "	" << "address" << a << std::endl;
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
