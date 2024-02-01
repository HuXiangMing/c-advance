// 4-30 RecycleSystem.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
// 一个回收系统  通过get 获取值  Recycle 归还

#include <iostream>
#include "RecycleSystem.h"


int main()
{
	std::cout << "---int---" << std::endl;
	{

		IntRecycleSystem intRecycleSystem;

		std::vector<int> int_vec;

		for (size_t i = 0; i < 5; i++)
		{
			int_vec.push_back(intRecycleSystem.Get());
		}

		for (int item : int_vec)
		{
			std::cout << item << std::endl;
			if (item % 2 == 0)intRecycleSystem.Recycle(item);
		}

		for (size_t i = 0; i < 5; i++)
		{
			int_vec.push_back(intRecycleSystem.Get());
		}

		for (int item : int_vec)
		{
			std::cout << item << std::endl;
		}

	}
	std::cout << "---string---" << std::endl;
	{
		StringRecycleSystem stringRecycleSystem;

		std::vector<std::string> str_vec;

		for (size_t i = 0; i < 5; i++)
		{
			str_vec.push_back(stringRecycleSystem.Get());
		}

		stringRecycleSystem.Recycle(str_vec[0]);
		stringRecycleSystem.Recycle(str_vec[2]);

		for (size_t i = 0; i < 5; i++)
		{
			str_vec.push_back(stringRecycleSystem.Get());
		}

		for (std::string item : str_vec)
		{
			std::cout << item << std::endl;
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
