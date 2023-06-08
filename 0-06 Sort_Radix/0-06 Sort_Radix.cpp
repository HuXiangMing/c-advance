// 0-06 Sort_Radix.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
// 基数排序

// 核心思想，按照元素的位数进行排序。先对元素的最低有效位进行排序，然后对次低有效位进行排序，直到对最高有效位进行排序，最终得到有序的数组。基数排序每轮迭代都可以确定当前位的顺序。

// 时间复杂度为 O(d(n+k))，其中 d 表示元素的最大位数，n 表示元素的数量，k 表示每一位的可能取值范围。
// 空间复杂度为 O(n)。

#include <iostream>
#include <algorithm>
#include <vector>

void radix_sort(int arr[], int len)
{
	int base = 1;//当前遍历的位数	
	int max = *std::max_element(arr, arr + len);//获取最大值

	std::vector<std::vector<int>> bucket(10);//定义10个桶

	while (pow(10, base - 1) < max)
	{

		for (size_t i = 0; i < len; i++)
		{
			//取得第base位
			int id = (int)(arr[i] / pow(10, base - 1)) % 10;//取得元素的第base位的数

			//将数放在对应的桶中
			bucket[id].push_back(arr[i]);

		}

		int temp_count = 0;

		//在依次取出
		for (size_t i = 0; i < 10; i++)
		{
			//如果桶里有元素就依次取出
			for (auto item : bucket[i])
			{
				arr[temp_count] = item;
				temp_count++;
			}
			//遍历完事清空桶中的数据
			bucket[i].clear();
		}

		base += 1;
	}
}

int main()
{
	int arr[10] = { 5,8,9,2,4,55,77,99,33,15 };
	int len = sizeof(arr) / sizeof(arr[0]);
	radix_sort(arr, len);
	//交换一次进行打印
	for (size_t i = 0; i < len; i++)
	{
		std::cout << arr[i] << " ";
	}
	std::cout << std::endl;
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
