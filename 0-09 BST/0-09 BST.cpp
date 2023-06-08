// 0-09 BST.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
// 二叉排序树

#include <iostream>


template <typename T>
class BST
{
public:
	BST() :root(nullptr) {};
	~BST() {};


	/// <summary>
	/// 比根节点小的放在左边，比根节点大的放在右边
	/// </summary>
	/// <param name="val"></param>
	void insert(T val)
	{
		root = insert_helper(root,val);
	}

private:
	struct Node
	{
		T data;
		Node* left;
		Node* right;
		Node(T data) :data(data), left(nullptr), right(nullptr) {};
	};

	Node* root;


	/// <summary>
	/// 将val与当前节点的值进行比较来决定插入到左边还是右边
	/// </summary>
	/// <param name="node">当前根节点</param>
	/// <param name="val">插入的值</param>
	/// <returns>插入成功后的节点</returns>
	Node* insert_helper(Node* node, T val)
	{
		if (node == nullptr)
		{
			node = new Node(val);
			return node;
		}

		//小于等于放在左边
		if (val <= node->data)
		{
			node->left = insert_helper(node->left,val);
		}
		else
		{
			node->right =insert_helper(node->right,val);
		}

		return node;
	}
};



int main()
{
	BST<int> bst;
	bst.insert(3);
	bst.insert(4);
	bst.insert(5);
	bst.insert(2);
	bst.insert(1);

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
