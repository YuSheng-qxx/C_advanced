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
//	//ƽ������
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
//		//�������������ڵ�
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
//		//����parentָ��
//		cur->_parent = parent;
//
//		//����ƽ������,��parent��ʼ
//		//���·�Χ��parent��ʼ->һֱ��root����·�ϵ����Ƚڵ�
//		while (parent)//�����Ǹղ���ڵ��ֱ�Ӹ��ڣ�Ҳ���������Ƚڵ�
//		{
//			if (parent->_left == cur)
//				parent->_bf--;
//			else
//				parent->_bf++;
//			//�ж�parent��ֵbf
//			if (parent->_bf == 0)//��-1��1�仯������
//				//parent�ڵ�ĳһ���������룬parent�ڵ�߶�û�з����仯����������
//				break;
//			else if (parent->_bf == 1 || parent->_bf == -1)//��0�仯������
//			{
//				//��������
//				cur = parent;
//				parent = parent->_parent;
//			}
//			else
//			{
//				//�������������´ﵽƽ��
//				if (parent->_bf == -2 && cur->_bf == -1)
//				{
//					//��ߵ���߸ߣ�����
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
//		//�������ĸ��ڵ�
//		Node* subL = parent->_left;
//		//���������������ĸ��ڵ�
//		Node* subLR = subL->_right;
//
//		subL->_right = parent;
//		parent->_left = subLR;
//
//		if (subLR)
//			subLR->_parent = parent;
//
//		//���parentΪ���ڵ㣬���¸��ڵ�
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
//		//����ƽ������
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