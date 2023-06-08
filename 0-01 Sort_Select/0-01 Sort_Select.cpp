// 0-01 Sort_Select.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
// 插入排序

//核心思想：每次从数组中选择一个最小的放在第一位，之后从后面继续选择一个最小的放在第二位，以此类推完成排序

//时间复杂度为O(n^2)，其中n是待排序的数组长度。 
//空间复杂度为O(1)，因为它不需要使用额外的空间来存储数组。
#include <iostream>


//插入排序
void sort_select(int arr[], int len)
{
	//记录最小值的下标
	int min_indext = 0;

	for (size_t i = 0; i < len - 1; i++)
	{
		int min_vale = arr[i];
		for (size_t j = i; j < len; j++)
		{
			//找到更小的储存直到最后一个
			if (min_vale > arr[j])
			{
				min_vale = arr[j];
				min_indext = j;
			}
		}

		arr[min_indext] = arr[i];
		arr[i] = min_vale;

		//交换一次进行打印
		for (size_t i = 0; i < len; i++)
		{
			std::cout << arr[i] << " ";
		}
		std::cout << std::endl;
	}

}



int main()
{

	int arr[10] = { 5,8,9,2,4,55,77,99,33,15 };
	int len = sizeof(arr) / sizeof(arr[0]);
	sort_select(arr, len);
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
