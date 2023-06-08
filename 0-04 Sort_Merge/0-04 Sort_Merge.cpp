// 0-04 Sort_Merge.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
// 归并排序

// 核心思想：分治法，将一个待排序数组不断的划分为两个子数组，直到每个子数组的长度为1，然后后在合并这些子数组，得到最终有序数组

// 时间复杂度为O(n*log(n))
// 空间复杂度为O(n)

// 对于时间复杂度，归并排序算法使用了分治思想，将待排序数组分为两个子数组，分别对每个子数组进行排序，然后将它们合并成一个完整的有序数组。
// 在分治的过程中，递归调用函数处理大小为n/2的两个子数组，一共进行了log n次，每次处理n个元素，因此为

#include <iostream>


void merge(int arr[], int l, int m, int r)
{

	//先将l - m  和 m+1 - r的数值进行缓存
	int n1 = m - l + 1;
	int n2 = r - m;
	int* L = new int[n1];
	int* R = new int[n2];

	for (size_t i = 0; i < n1; i++)
	{
		L[i] = arr[l + i];
	}

	for (size_t j = 0; j < n2; j++)
	{
		R[j] = arr[m + 1 + j];
	}



	int i = 0, j = 0, k = l;

	//归并并排序
	while (i < n1 && j < n2)
	{
		//归并
		if (L[i] < R[j])
		{

			arr[k] = L[i];
			i++;
		}
		else
		{
			arr[k] = R[j];
			j++;
		}
		k++;
	}

	//有可能左边或右边归并完成，导致另一边还有数据并没有完全归并到数组中

	//左边没有归并完成
	while (i < n1)
	{
		arr[k] = L[i];
		i++; k++;
	}

	//右边没有归并完成
	while (j < n2)
	{
		arr[k] = R[j];
		j++; k++;
	}

	delete[] L;
	delete[] R;



	//交换一次进行打印
	for (size_t i = 0; i <= r - l; i++)
	{
		std::cout << arr[l + i] << " ";
	}
	std::cout << std::endl;

}


void sort_merge(int arr[], int l, int r)
{
	if (l < r)
	{
		//拆分
		int m = l + (r - l) / 2;//选择中间值进行拆分 , l+(r-l)才能定位到当前数组的中间值
		sort_merge(arr, l, m);//左边的继续拆分
		sort_merge(arr, m + 1, r);//右边的继续拆分

		merge(arr, l, m, r);
	}
}



int main()
{
	int arr[10] = { 5,8,9,2,4,55,77,99,33,15 };
	int len = sizeof(arr) / sizeof(arr[0]);
	sort_merge(arr, 0, len - 1);
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
