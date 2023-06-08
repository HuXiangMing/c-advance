// 0-10AVLTree.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
// 平衡二叉树
// 平衡二叉树的任意节点的子树的高度差都小于等于1


#include <iostream>
#include <queue>
#include <string>
#include <sstream>
using namespace std;

//平衡二叉树
class AVLTree
{
public:
	struct Node
	{
		int val;
		Node* left;
		Node* right;
		Node(int v) :val(v), left(nullptr), right(nullptr) {};
	};

	AVLTree() :root(nullptr) {};
	~AVLTree() {};

	void insert(int val)
	{
		//插入：小于根节点的放在左边，大于根节点的放在右边		
		root = insert_helper(root, val);

	}
	void erase(int val)
	{
		root = erase_helper(root, val);
	}


	size_t size()
	{
		return size_helper(root);
	}

	//中序遍历->从小到大
	void log_inorder()
	{
		log_inoder_helper(root);
	}


	//按行输出
	void log_line()
	{
		queue<Node*> q;

		if (root != nullptr)q.push(root);

		while (q.empty() == false)
		{
			int size = q.size();
			stringstream ss;

			//这里一定要使用固定大小的size，这样在for循环里入队的节点才不会收到size影响而打印错乱
			for (size_t i = 0; i < size; i++)
			{
				Node* front_node = q.front();
				//拼接字符
				ss << front_node->val << " ";
				q.pop();

				//添加子节点入队到末尾
				if (front_node->left != nullptr)
					q.push(front_node->left);
				if (front_node->right != nullptr)
					q.push(front_node->right);

			}
			//输出
			cout << ss.str() << endl;
		}
	}

private:


	Node* root;


	/// <summary>
	/// 根据值删除一个节点
	/// </summary>
	/// <param name="node">根节点</param>
	/// <param name="val">值</param>
	/// <returns>总根点</returns>
	Node* erase_helper(Node* node, int val)
	{
		if (node == nullptr)
		{
			return nullptr;
		}

		//1.找到删除值所在的节点
		else if (val < node->val)
		{
			//往左找
			node->left = erase_helper(node->left, val);
		}
		else if (val > node->val)
		{
			//往右找
			node->right = erase_helper(node->right, val);
		}
		else//找到了，进行删除
		{
			//该节点为叶子节点，或左右有一个为空节点，可以直接进行删除
			if (node->left == nullptr || node->right == nullptr)
			{
				Node* temp_node = node->left ? node->left : node->right;

				if (temp_node == nullptr)
				{
					//左右子节点都为nullptr	
					temp_node = node;
					node = nullptr;
				}
				else
				{
					*node = *temp_node;//修改里面的值为子节点的值
				}

				//释放子节点的内存
				delete temp_node;
			}
			else
			{
				//拿到右侧节点的最小值或者左侧节点的最大值进行替换
				Node* temp_node = get_min_node(node->right);//右侧节点的最小值

				node->val = temp_node->val;//修改里面的值为子节点的值

				//释放子节点的内存
				//delete temp_node;不可以直接释放，
				//1：如果直接释放temp_node，有可能temp_node父节点的右侧可能有值，删除会出现问题。
				//2：如果直接释放temp_node，node->right的结构也会发生变化，可能是不平衡的
				//应递归遍历找到右子树的最小值进行删除->这时会走到上面的逻辑node->left == nullptr || node->right == nullptr
				node->right = erase_helper(node->right, temp_node->val);
			}
		}

		//2.进行平衡处理

		if (node == nullptr) return nullptr;//删除的根节点

		return balance(node);

	}


	/// <summary>
	/// 获取当前节点的最大值节点
	/// </summary>
	/// <param name="node">根节点</param>
	/// <returns>最大值节点</returns>
	Node* get_max_node(Node* node)
	{
		if (node != nullptr && node->right != nullptr)
		{
			return get_max_node(node->right);
		}

		return node;
	}

	/// <summary>
	/// 获取当前节点的最小值节点
	/// </summary>
	/// <param name="node">根节点</param>
	/// <returns>最小值节点</returns>
	Node* get_min_node(Node* node)
	{
		if (node != nullptr && node->left != nullptr)
		{
			return get_min_node(node->left);
		}

		return node;
	}


	/// <summary>
	/// 递归遍历找到某个值插入的节点位置,并进行平衡
	/// </summary>
	/// <param name="node">当前正在查找的节点</param>
	/// <param name="val">要插入的值</param>
	/// <returns>平衡后的根节点</returns>
	Node* insert_helper(Node* node, int val)
	{
		//从头结点开始遍历，若小于父节点则放在左边，若大于父节点则放在右边
		if (node == nullptr)
		{
			return new Node(val);
		}

		//比较后，递归获取子节点，直到找到子节点为空的节点，进行插入, 并依次进行二叉树平衡处理
		if (val < node->val)
		{
			//小于当前结点的值放在左侧			
			node->left = insert_helper(node->left, val);
		}
		else if (val > node->val)
		{
			//大于当前结点的值放在右侧
			node->right = insert_helper(node->right, val);
		}

		// 因为是递归遍历查找插入，因为每次插入查找时找到的是一个叶子（最尾部）节点，所以依次由下网上进行平衡，最后平衡的肯定是根节点
		return balance(node);
	}



	/// <summary>
	/// 右旋->将根节左侧节点设置为新的根节点，新的根节点右侧设置为旧的根节点
	/// </summary>
	/// <param name="node">需要调整的头节点</param>
	/// <returns>右旋后的根节点</returns>
	Node* right_rotate(Node* node)
	{
		//定义一个新的头节点为根节点的左侧节点
		Node* new_node = node->left;
		//因为原来根节点的左侧是有值的，且新节点的右侧节点是多出来的，且大于new_node 小于node，刚好可以放在node的左侧
		node->left = new_node->right;
		//将新节点的右侧设置为原来的根节点
		new_node->right = node;
		return new_node;
	}

	/// <summary>
	/// 左旋->将根节点的右侧节点设置为新的根节点，将新根节点的左侧设置为旧的根节点
	/// </summary>
	/// <param name="node">需要调整的头节点</param>
	/// <returns>左旋后的根节点</returns>
	Node* left_rotate(Node* node)
	{
		//与右旋逻辑一样,方向相反
		Node* new_node = node->right;//定义个头指针指向node->right;
		node->right = new_node->left;//将node->right 指针的指向修改为new_node->right
		new_node->left = node;//头指针左侧指针指向node
		return new_node;
	}


	/// <summary>
	/// 检测平衡状态
	/// </summary>
	/// <param name="node">新插入的节点</param>
	Node* balance(Node* node)
	{
		//从根节点，依次判断左右两边的高度时候平衡	

		int bf = get_balance_factor(node);

		if (bf > 1)
		{
			//左侧高于右侧
			//判断旋转类型
			if (get_balance_factor(node->left) < 0)
			{
				//左侧子节点的右侧一定有值
				//LR型旋转 -> 先左在右
				node->left = left_rotate(node->left); //转为LL型
			}

			//LL型
			node = right_rotate(node);
		}

		if (bf < -1)
		{
			//右侧高于左侧
			//判断旋转类型
			if (get_balance_factor(node->right) > 0)
			{
				//右侧子节点的左侧一定有值
				//RL型旋转 -> 先右在左

				//更换根节点 ->这种RL型旋转需先转换为RR型 ->所以应更换node->right的根节点
				node->right = right_rotate(node->right);
				//变为 RR型 
			}

			//新添加的节点在右侧
			//RR型旋转 -> 左旋
			node = left_rotate(node);
		}

		return node;
	}


	/// <summary>
	/// 获取当前节点的高度
	/// </summary>
	/// <param name="node">当前节点</param>
	/// <returns>高度</returns>
	int	node_height(Node* node)
	{
		if (node != nullptr)
		{
			return std::max(node_height(node->left), node_height(node->right)) + 1;
		}
		return 0;
	}

	/// <summary>
	/// 获取当前节点的平衡因子
	/// </summary>
	/// <param name="node">当前节点</param>
	/// <returns>当前节点的平衡因子</returns>
	int get_balance_factor(Node* node)
	{
		if (node == nullptr)
		{
			return 0;
		}

		return node_height(node->left) - node_height(node->right);
	}


	/// <summary>
	/// 获取父节点
	/// </summary>
	/// <param name="node">目标节点</param>
	/// <returns>目标节点的父节点</returns>
	Node* find_parent_ndoe(Node* node)
	{
		Node* parent_node = nullptr;
		Node* currt_node = root;

		while (currt_node != nullptr)
		{
			if (currt_node->val == node->val)
			{
				break;
			}

			if (currt_node->val < node->val)
			{
				//比较左边
				parent_node = currt_node;
				currt_node = currt_node->left;
			}

			if (currt_node->val > node->val)
			{
				//比较右边
				parent_node = currt_node;
				currt_node = currt_node->right;
			}
		}

		return parent_node;
	}




	size_t size_helper(Node* node)
	{
		if (node == nullptr)
		{
			return 0;
		}
		else
		{
			return size_helper(node->left) + size_helper(node->right) + 1;
		}
	}


	/// <summary>
	/// 递归中序打印
	/// </summary>
	/// <param name="node">根节点</param>
	void log_inoder_helper(Node* node)
	{
		if (node != nullptr)
		{
			log_inoder_helper(node->left);
			cout << node->val << " ";
			log_inoder_helper(node->right);
		}

		//在结尾换行
		if (node == root)
		{
			cout << endl;
		}
	}

};


int main()
{
	AVLTree avlTree;
	avlTree.insert(16);
	avlTree.insert(3);
	avlTree.insert(7);
	avlTree.insert(11);
	avlTree.insert(9);
	avlTree.insert(26);
	avlTree.insert(18);
	avlTree.insert(14);
	avlTree.insert(15);
	avlTree.insert(17);
	avlTree.log_line();
	avlTree.erase(16);
	avlTree.log_line();
	avlTree.log_inorder();


	std::cout << avlTree.size();
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
