// 0-08 Sort_Quick.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
// 快速排序

// 核心思想：选择一个基准数，从右边开始一直找到比基准数小的进行交换，在从左边开始找到比基准数大的进行交换，循环往复，直到左边遍历的索引等于右边遍历的索引。这样就确定好基准数的位置了


// 时间复杂度为 O(nlogn)，其中 n 是排序数组的长度。在最坏情况下，即待排序数组已经有序或近似有序，时间复杂度会退化为 O(n^2)。
// 空间复杂度为 O(logn)，其中 logn 是递归树的深度。在最坏情况下，递归树的深度为 n，此时空间复杂度为 O(n)。
#include <iostream>


void quick_sort(int arr[], int l, int r)
{
	//l >= r时。基准数的位置已经确定
	if (l >= r) return;

	int pivot = arr[l]; //设定arr[l]为基准点
	int i = l, j = r;

	while (i < j)//左右两边还有数据没有找完
	{
		//从右边开始找,找到比基准数小的，与i索引进行交换
		while (i < j && arr[j] > pivot) { j--; }
		arr[i] = arr[j];

		//从左侧开始找，找到比基准数大的，与j索引进行交换
		while (i < j && arr[i] < pivot) { i++; }
		arr[j] = arr[i];
	}

	//填充ij索引的位置  此时i=j
	arr[i] = pivot;


	//打印每一次选择排序的结果
	std::cout << "pivot:" << pivot << " [";
	for (size_t i = 0; i < r; i++)
	{
		std::cout << " " << arr[i] << " ";
	}
	std::cout << "]" << std::endl;


	//对左右边改变分别进行选择排序
	int half = l + ((r -l) / 2);
	quick_sort(arr, l, half);
	quick_sort(arr, half+1, r);

}

int main()
{
	int arr[10] = { 5,8,9,2,4,55,77,99,33,15 };
	int len = sizeof(arr) / sizeof(arr[0]);
	quick_sort(arr, 0,len-1);
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
