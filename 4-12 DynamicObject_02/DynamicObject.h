#pragma once

class IObject
{
public:
	virtual void Init() = 0;
	virtual void Start() = 0;
	virtual void Update() = 0;
private:

};

enum DynamicType
{
	Object,
	Data,
	Manager,
	UI
};

//动态对象基类
class DynamicObject:public IObject
{
public:
	DynamicObject() 
	{
		dynamicType = DynamicType::Object;
	};

	const DynamicType GetDynamicType() { return dynamicType; }

	virtual void Init() {};
	virtual void Start() {};
	virtual void Update() {};

	virtual ~DynamicObject() {};

protected:

	DynamicType dynamicType;
};

