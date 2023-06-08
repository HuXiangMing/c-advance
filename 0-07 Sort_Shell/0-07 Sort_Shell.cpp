// 0-07 Sort_Shell.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
// 希尔排序 插入的改进

// 核心思想：选择一个增量序列，一般为n/2，将原序列分成若干个子序列，相隔增量数的元素划分为一组，进行插入排序。再将增量/2，在进行插入排序，直到增连改为0

#include <iostream>


void shell_sort(int arr[], int len)
{
	//选择增量
	int gap = len / 2;

	//如果增量大于0，则继续进行插入排序
	while (gap > 0)
	{
		//从gap 开始依次往后遍历
		for (size_t i = gap; i < len; i++)
		{
			int j = i; //选择的索引
			int temp = arr[i]; //选择的值

			//循环跟前面j-gap的值相比较，如果小于前面的值，则进行交换
			while (j > gap && temp < arr[j - gap]) // 不能使用 j >= 0 ，当j=1或0时， j-gap可能为负
			{
				arr[j] = arr[j - gap];
				j -= gap;
			}

			arr[j] = temp;//因为前面比较的是j和j-gap,之后在执行j -= gap;此时的j（坑位）就是与temp交换的位置
		}

		gap /= 2;

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
	shell_sort(arr, len);
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
 