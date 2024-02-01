#pragma once
#include "DynamicObject.h"
#include <map>
#include <string>

// ��̬���󴴽�����
class DynamicFactory
{
public:

	//���ڶ�̬���ض���
	using CreatHander = DynamicObject*(*)();

	static DynamicFactory& Instance()
	{
		static DynamicFactory fac;
		return fac;
	}

	static std::string ReadTypeName(const char* name)
	{
		//strstr ����ƥ����һ���ַ��״γ��ֵ�λ�ã�������ڣ��򷵻�ָ���λ�õ�ָ�룬���򷵻�NULL
		const char* p = strstr(name, " ");
		if (p)
		{
			size_t prev_len = (size_t)(p - name);
			//memcmp ���ڱȽ������ַ�����ǰN���ֽ�  �����ͬ����0
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


	//�洢���ͺͶ���
	std::map<std::string, CreatHander> create_function_map;

};
