// 1-01 Vector_Array.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
// 使用数组实现的一个Vector

#include <iostream>
#include <chrono>

//std::vector 是通过数组实现的动态数组
//std::vector 适用于需要快速随机访问元素的场景
template <typename T>
class Vector
{
public:
	Vector() :_size(0), _capacity(0), _data(nullptr) {};
	~Vector() { delete[] _data; }

	//获取容器大小
	size_t size()
	{
		return _size;
	}

	//将元素添加到末尾
	void push_back(const T& val)
	{
		//检查容量是否足够
		if (_capacity == _size)
		{
			//无空间，需扩充
			resize();
		}

		//添加数据
		_data[_size] = val;

		//更新元素个数
		_size++;
	}

	//删除末尾的元素
	void pop_back()
	{
		if (_size > 0)
		{
			_size--;//虽然只是强行修改了元素个数，末尾的值依然还存在，但却无法获取，并且在push_back时会修改为期望的值
		}
	}

	//获取指定位置的元素
	T& operator[](const size_t index)
	{
		//是否操作最大元素个数
		if (!is_in_range(index)) {};

		return _data[index];

	}

	//插入元素到指定位置
	void insert(size_t index, const T& val)
	{

		if (!is_in_range(index)) return;


		if (_size == 0)
		{
			push_back(val);
			return;
		}

		if (_capacity == _size)
		{
			//无空间，需扩充
			resize();
		}

		//插入

		// 将 pos 及其之后的元素往后移一位
		for (size_t i = _size; i > index; --i)
		{
			//1.
			//定位 new 运算符构造新的元素,使用std::move 将元素从一个位置移动到另一个位置，避免了不必要的拷贝操作。
			//new (&_data[i])T(std::move(_data[i - 1]));//在 _data[size]该地址创建一个新对象，值为_data[size - 1]
			////显式析构操作
			//_data[i - 1].~T();

			//2.
			_data[i] = std::move(_data[i - 1]);

		}

		_data[index] = val;
		_size++;

	}

	//删除指定位置的元素
	void erase(size_t index)
	{
		//检查一下
		if (!is_in_range(index)) return;

		if (_size > 0)
		{
			for (size_t i = index; i < _size - 1; i++)
			{

				_data[i] = std::move(_data[i + 1]);
			}

			_size--;
		}


	}


	void clear()
	{
		delete[] _data;
		_data = nullptr;
		_size = 0; _capacity = 0;
	}


	void log()
	{
		for (size_t i = 0; i < _size; i++)
		{
			std::cout << _data[i] << " ";
		}

		std::cout << std::endl;
	}

private:
	// 动态数组的指针
	T* _data;

	// 元素个数
	size_t _size; //size_t 是一种无符号整数类型，用于表示内存大小、数组索引和对象大小等非负整数值。

	// 数组的容量
	size_t _capacity;

	// 扩充容器的容量释放原来的内存并拷贝数据
	void resize()
	{
		_capacity = (_capacity == 0) ? 1 : _capacity * 2;//2倍扩充
		T* newData = new T[_capacity];
		//填充数据
		for (size_t i = 0; i < _size; i++)
		{
			newData[i] = _data[i];
			//*(newData + i) = *(_data + i);
		}

		//释放原来的内存
		delete[] _data;
		//将原来的指针指向新创建的内存地址
		_data = newData;
	}

	//判断索引是否在范围内
	bool is_in_range(size_t index, bool is_throw = true)
	{
		//刚初始化好，只能在0号位置上
		if (_size == 0 && index == 0) return true;

		if (index < _size)	return true;

		if (is_throw)
		{
			throw std::out_of_range("index out of range");
		}

		return false;
	}
};

int main()
{

	{
		Vector<int> vector;

		for (size_t i = 0; i < 10; i++)
		{
			vector.push_back(i);
		}

		vector.log();

		for (size_t i = 0; i < 10; i++)
		{
			if (i % 2 == 0)
			{
				vector.pop_back();
			}
		}

		vector[0] = 100;
		vector.insert(4, 200);
		vector.log();

		vector.erase(vector.size() - 1);
		vector.log();

		vector.clear();
		vector.push_back(1);
		vector.log();
	}

	//时间对比 插入
	{
		int i = 100000;
		Vector<int> vector;

		// 获取当前时间点
		auto start = std::chrono::high_resolution_clock::now();
		while (i > 0)
		{
			//vector.push_back(i);//普通插入
			vector.insert(vector.size()/2,0);//随机插入,数量很大时非常慢
			i--;
		}		

		//int a = vector[10000000-1];
		vector.erase(0);

		// 获取结束时间点
		auto end = std::chrono::high_resolution_clock::now();
		// 计算时间差
		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
		// 输出计时结果
		std::cout << "Time elapsed: " << duration.count() << " microseconds." << std::endl;
		std::cout << "size:" << vector.size() << std::endl;
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
