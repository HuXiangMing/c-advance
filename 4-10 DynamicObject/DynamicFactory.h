#pragma once
#include "DynamicObject.h"
#include <map>
#include <string>

// 动态对象创建工厂
class DynamicFactory
{
public:

	//用于动态返回对象
	using CreatHander = DynamicObject*(*)();

	static DynamicFactory& Instance()
	{
		static DynamicFactory fac;
		return fac;
	}

	static std::string ReadTypeName(const char* name)
	{
		//strstr 用于匹配另一个字符首次出现的位置，如果存在，则返回指向该位置的指针，否则返回NULL
		const char* p = strstr(name, " ");
		if (p)
		{
			size_t prev_len = (size_t)(p - name);
			//memcmp 用于比较两个字符串的前N个字节  如果相同返回0
			if (memcmp(name, "class", prev_len) == 0 ||
				memcmp(name, "struct", prev_len) == 0 ||
				memcmp(name, "enum", prev_len) == 0 ||
				memcmp(name, "union", prev_len) == 0)
			{
				p += 1;
				return std::string(p);
			}
		}
		return std::string(name);
	}

	bool Regist(std::string name, CreatHander fun)
	{
		if (!fun) return false;

		std::string type_name = ReadTypeName(name.c_str());
		return create_function_map.insert(std::make_pair(type_name, fun)).second;
	}


	template<typename T , class = typename std::enable_if<std::is_base_of<DynamicObject, T>::value>::type>
	T* Create(const std::string& type_name)
	{
		auto it = create_function_map.find(type_name);

		if (it == create_function_map.end())
		{
			throw std::exception("Create Failed!");
			return nullptr;
		}

		DynamicObject* obj = it->second();
		if (!obj)
		{
			return NULL;
		}
		T* real_obj = dynamic_cast<T*>(obj);
		if (!real_obj)
		{
			delete obj;
			return NULL;
		}
		return real_obj;
	}


	//存储类型和对象
	std::map<std::string, CreatHander> create_function_map;

};
