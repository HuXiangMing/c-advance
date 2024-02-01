#pragma once

#include <assert.h>
#include "DynamicFactory.h"

// ��̬���󴴽���
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
		registor.do_nothing();//����Registor���캯��������ע�ͣ����registorû�б��������ⲿ�����ľ�̬��Ա�ᱻ�Ż��������޷����빹�캯����
	}

	virtual ~DynamicCreate()
	{
		registor.do_nothing();
	}

};

//ģ��ľ�̬��Ա�Ƚ����⣬���������涨�����£�����һ��DynamicCreate<T>::Registor �ľ�̬��Աregistor
template <typename T>
typename DynamicCreate<T>::Registor DynamicCreate<T>::registor;//Ϊregistor�����ڴ�ռ�
