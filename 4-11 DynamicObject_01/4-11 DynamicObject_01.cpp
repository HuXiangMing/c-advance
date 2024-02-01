// 4-02 DynamicObject_01.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
// 完全自动创建，由dynamicManager负责管理
// 只限定了DynamicCreate的子类

// 一般用在需要程序一运行自动创建的对象，一般为管理模块

#include <iostream>
#include "DynamicCreate.h"
#include "DynamicManager.h"

class Dynamic_TestA : public DynamicCreate<Dynamic_TestA>
{
public:
    Dynamic_TestA() { printf("Dynamic_TestA 构造\n"); };

    void Init() override
    {
        printf("Dynamic_TestA init\n");
    }

    void Start() override
    {
        printf("Dynamic_TestA start\n");
    }
};

namespace Dynamic
{
    class Dynamic_TestB : public DynamicCreate<Dynamic_TestB>
    {
    public:
        Dynamic_TestB() { printf("Dynamic_TestB 构造\n"); };
    };
}

int main()
{
    DynamicManager& mgr = DynamicManager::Instance();
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
