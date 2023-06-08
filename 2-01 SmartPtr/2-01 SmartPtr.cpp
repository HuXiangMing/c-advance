// 2-01 SmartPtr.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>


/// <summary>
/// 实现原理，使用引用计数，在构造和析构时进行增加或删除，当引用计数为0时，销毁该指针所指向的内存
/// </summary>
/// 


template <typename T>
class SmartPtr
{
public:
	/// <summary>
	/// 初始化使用在外部new出来，进行维护
	/// </summary>
	/// <param name="t"></param>
	SmartPtr(T* t):data(nullptr), ref_count(nullptr)
	{
		if (t != nullptr)
		{
			data = t;
			ref_count = new size_t(1);
		}		
	};

	//拷贝构造
	SmartPtr(const SmartPtr<T>& smartPtr)
	{
		if (smartPtr.data)
		{
			data = smartPtr.data;
			ref_count = smartPtr.ref_count;
			*ref_count += 1;
		}
		//未初始化不进行引用+1

	}


	//拷贝复制运算符
	SmartPtr<T>& operator=(const SmartPtr<T> smartPtr)
	{
		if (&smartPtr != this)
		{
			//ref_count为1直接释放
			if (ref_count && (--(*ref_count) == 0))
			{
				delete data;
				delete ref_count;
			}


			if (smartPtr.data)
			{
				data = smartPtr.data;
				ref_count = smartPtr.ref_count;
				*ref_count += 1;
			}
			else
			{
				//传过来的对象未初始化
				data = nullptr;
				ref_count = nullptr;
			}
		}	

		return *this;
	}

	~SmartPtr()
	{
		if (ref_count && (--(*ref_count) == 0))
		{
			delete data;
			delete ref_count;
			data = nullptr, ref_count = nullptr;
		}

	};



	T& operator*()
	{
		return *data;
	}

	T* operator->()
	{
		return data;
	}

private:
	T* data;
	size_t* ref_count;
};



int main()
{

	{
		SmartPtr<int> p(new int(5));

		SmartPtr<int> q(new int(5));

		SmartPtr<int> p1 = p;

		int* i = new int(10);
		SmartPtr<int> p2(i);//测试

		p1 = q;
		
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
