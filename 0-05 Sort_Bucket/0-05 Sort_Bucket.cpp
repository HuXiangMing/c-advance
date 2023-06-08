// 0-05 Sort_Bucket.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
// 桶排序

// 核心思想：将元素按照某种规则依次映射到各个桶中，然后分别堆桶中的元素进行排序，之后在进行合并

// 时间复杂度为 O(n + k)，其中 n 表示排序的元素数量，k 表示桶的数量。
// 因为桶的数量需要根据数据集合中元素的范围来确定，因此桶排序不适合对于数据值范围非常大的数据集合进行排序。
// 在这种情况下，桶的数量会很大，导致空间复杂度变高，时间复杂度也会随之受到影响。

// 桶排序的空间复杂度为 O(n + k)，其中 n 表示排序的元素数量，k 表示桶的数量。
// 在最坏情况下，每个桶只包含一个元素，此时需要 n 个桶，因此空间复杂度为 O(n)。
// 在最好情况下，所有的元素都落在同一个桶中，此时只需要 k 个桶，因此空间复杂度为 O(k)。
#include <iostream>
#include <algorithm>
#include <vector>

//在桶中使用插入排序
void sort_insert(int arr[], int len)
{
	for (size_t i = 1; i < len; i++)
	{
		int temp = arr[i];
		int j = i - 1;

		while (j>=0 && arr[j] > temp)
		{
			arr[j + 1] = arr[j];
			j--;
		}

		arr[j + 1] = temp;
	}

	//交换一次进行打印
	for (size_t i = 0; i < len; i++)
	{
		std::cout << arr[i] << " ";
	}
	std::cout << std::endl; 
}


void sort_bucket(int arr[], int len)
{
	//先取得最大值和最小值
	int max = *std::max_element(arr, arr + len);
	int min = *std::min_element(arr, arr + len);

	//分散在各个桶里
	std::vector<std::vector<int>> bucket(3);
	int average = (max - min) / 3;//均值，进行映射

	for (size_t i = 0; i < len; i++)
	{
		int bucket_indext = (arr[i] - average) / average;

		bucket[bucket_indext].push_back(arr[i]);
	}

	//对每个桶进行选择排序
	for (size_t i = 0; i < 3; i++)
	{
		sort_insert(bucket[i].data(), bucket[i].size());
	}

	//归并到原数组中
	int indext = 0;
	for (size_t i = 0; i < 3; i++)
	{
		for (auto v : bucket[i])
		{
			arr[indext] = v;
			indext++;
		}
	}
}


int main()
{

	int arr[10] = { 5,8,9,2,4,55,77,99,33,15 };
	int len = sizeof(arr) / sizeof(arr[0]);
	sort_bucket(arr, len);
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
