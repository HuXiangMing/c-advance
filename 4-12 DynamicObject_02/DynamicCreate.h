#pragma once

#include <assert.h>
#include "DynamicFactory.h"

// 动态对象创建器
template<typename T>
class DynamicCreate : public DynamicObject
{

public:
	static DynamicObject* CreateObject()
	{
		return new T();
	}

	struct Registor
	{
		Registor()
		{
			if (!DynamicFactory::Instance().Regist(typeid(T).name(), CreateObject))
			{
				assert(false);
			}
		}

		inline void do_nothing()const { }
	};


	static Registor registor;

public:
	DynamicCreate()
	{
		registor.do_nothing();//触发Registor构造函数，不能注释，如果registor没有被引用则，外部声明的静态成员会被优化掉导致无法进入构造函数中
	}

	virtual ~DynamicCreate()
	{
		registor.do_nothing();
	}

};

//模板的静态成员比较特殊，必须在外面定义如下，定义一个DynamicCreate<T>::Registor 的静态成员registor
template <typename T>
typename DynamicCreate<T>::Registor DynamicCreate<T>::registor;//为registor分配内存空间
