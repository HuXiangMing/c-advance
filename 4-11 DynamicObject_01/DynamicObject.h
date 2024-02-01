#pragma once

class IObject
{
public:
	virtual void Init() = 0;
	virtual void Start() = 0;
	virtual void Update() = 0;
private:

};

//动态对象基类
class DynamicObject:public IObject
{
public:
	DynamicObject() {};

	virtual void Init() {};
	virtual void Start() {};
	virtual void Update() {};

	virtual ~DynamicObject() {};
};