//#include<iostream>
//using namespace std;
//
//template<class T>
//struct AVLTreeNode
//{
//	T _data;
//	AVLTreeNode<T>* _left;
//	AVLTreeNode<T>* _right;
//	AVLTreeNode<T>* _parent;
//	//平衡因子
//	int _bf;
//
//	AVLTreeNode(const T& val = T())
//		:_data(val)
//		, _left(nullptr)
//		, _right(nullptr)
//		, _parent(nullptr)
//		, _bf(0)
//	{}
//};
//
//template<class T>
//class AVLTree
//{
//public:
//	typedef AVLTreeNode<T> Node;
//
//	bool insert(const T& val)
//	{
//		//空树，创建根节点
//		if (_root == nullptr)
//		{
//			_root = new Node;
//			_root->_data = val;
//			return true;
//		}
//		Node* cur = _root;
//		Node* parent = nullptr;
//		while (cur)
//		{
//			parent = cur;
//			if (cur->_data == val)
//				return false;
//			else if (cur->_data > val)
//				cur = cur->_left;
//			else
//				cur = cur->_right;
//		}
//		cur = new Node(val);
//		if (parent->_data > val)
//			parent->_left = cur;
//		else
//			parent->_right = cur;
//
//		//连接parent指针
//		cur->_parent = parent;
//
//		//更新平衡因子,从parent开始
//		//更新范围：parent开始->一直到root这条路上的祖先节点
//		while (parent)//可能是刚插入节点的直接父节，也可能是祖先节点
//		{
//			if (parent->_left == cur)
//				parent->_bf--;
//			else
//				parent->_bf++;
//			//判断parent的值bf
//			if (parent->_bf == 0)//从-1或1变化过来的
//				//parent节点某一个子树补齐，parent节点高度没有发生变化，结束更新
//				break;
//			else if (parent->_bf == 1 || parent->_bf == -1)//从0变化过来的
//			{
//				//继续更新
//				cur = parent;
//				parent = parent->_parent;
//			}
//			else
//			{
//				//调整搜索数重新达到平衡
//				if (parent->_bf == -2 && cur->_bf == -1)
//				{
//					//左边的左边高，右旋
//					RotateR(parent);
//				}
//				else if (parent->_bf == 2 && cur->_bf == 1)
//				{
//					RotateL(parent);
//				}
//
//				break;
//			}
//		}
//		return true;
//	}
//	void RotateR(Node* parent)
//	{
//		//左子树的根节点
//		Node* subL = parent->_left;
//		//左子树的右子树的根节点
//		Node* subLR = subL->_right;
//
//		subL->_right = parent;
//		parent->_left = subLR;
//
//		if (subLR)
//			subLR->_parent = parent;
//
//		//如果parent为根节点，更新根节点
//		if (parent == _root)
//		{
//			_root = subL;
//			subL->_parent = nullptr;
//		}
//		else
//		{
//			Node* pparent = parent;
//			if (parent->_left == parent)
//				pparent->_left = subL;
//			else
//				pparent->_right = subL;
//			subL->_parent = pparent;
//		}
//		parent->_parent = subL;
//		//更新平衡因子
//		parent->_bf = subL->_bf = 0;
//	}
//
//	void RotateL(Node* parent)
//	{
//		Node* subR = parent->_right;
//		Node* subRL = subR->_left;
//		subR->_left = parent;
//		parent->_right = subRL;
//		if (subRL)
//		{
//			subRL->_parent = parent;
//		}
//		if (parent == _root)
//		{
//			_root = subR;
//			subR->_parent = nullptr;
//		}
//		else
//		{
//			Node* pparent = subR->_parent;
//			if (pparent->_left == parent)
//				pparent->_left = subR;
//			else
//				pparent->_right = subR;
//			subR->_parent = pparent;
//		}
//		parent->_parent = subR;
//		subR->_bf = subRL->_bf = 0;
//	}
//
//private:
//	Node* _root = nullptr;
//};
//
//void test()
//{
//	AVLTree<int> av1;
//	av1.insert(60);
//	av1.insert(30);
//	av1.insert(65);
//	av1.insert(15);
//	av1.insert(50);
//	av1.insert(10);
//
//}
//
//int main()
//{
//	test();
//	system("pause");
//	return 0;
//}