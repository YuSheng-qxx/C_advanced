#include<iostream>
#include<utility>
#include<time.h>
using namespace std;

enum COLOR
{
	BLACK,
	RED
};

template<class K,class V>
struct RBNode
{
	RBNode<K, V>* _parent;
	RBNode<K, V>* _left;
	RBNode<K, V>* _right;
	//����Ϊkey-value��ֵ��
	pair<K, V> _kv;
	//�ڵ����ɫ
	//bool _color;  // STL��ʵ��
	COLOR _color;

	//�ڵ���ɫĬ��Ϊ��ɫ
	RBNode(const pair<K, V> kv = pair<K, V>())
		:_parent(nullptr)
		, _left(nullptr)
		, _right(nullptr)
		, _kv(kv)
		, _color(RED)
	{}
};

//������������� ��ԭ��ָ�룬��װ�ڵ㣬
//������Ϊ����
template <class K, class V>
struct _RBTreeIterator
{
	typedef RBNode<K, V> Node;
	typedef _RBTreeIterator<K, V> Self;

	//��װNode
	Node* _node;
	_RBTreeIterator(Node* node)
		:_node(node)
	{}

	pair<K, V>& operator*()
	{
		//��ȡ�ڵ��е�����
		return _node->_kv;
	}

	pair<K, V>* operator->()
	{
		//��ȡ�ڵ������ݵ�ָ��
		return &_node->_kv;
	}

	bool operator!=(const Self& it)
	{
		return _node != it._node;
	}
	//�����ƶ��� �����
	Self& operator++()
	{
		//�ж��Ƿ���������
		if (_node->_right)
		{
			//��һ��Ҫ���ʵĽڵ㣺 ������������ڵ�
			_node = _node->_right;
			while (_node->_left)
				_node = _node->_left;
		}
		else
		{
			//�����������ڣ�
			//��һ��Ҫ���ʵĽڵ㣺 ���ڵ�--> �θ��ڵ�ĺ��ӽڵ㲻��������
			Node* parent = _node->_parent;
			while (_node == parent->_right)
			{
				_node = parent;
				parent = parent->_parent;
			}
			if (_node->_right != parent)
				_node = parent;
		}
		return *this;
	}

	//�Ҹ���
	Self& operator--()
	{
		//���������ڣ� �����������ҽڵ�
		if (_node->_left)
		{
			_node = _node->_left;
			while (_node->_right)
				_node = _node->_right;
		}
		else
		{
			//�����������ڣ��Ҹ��ڵ㣺 ���ĺ��Ӳ���������
			Node* parent = _node->_parent;
			while (_node == parent->_left)
			{
				_node = parent;
				parent = parent->_parent;
			}

			if (_node->_left != parent)
				_node = parent;
		}
		return *this;
	}
};

template<class K, class V>
class RBTree
{
public:
	typedef RBNode<K, V> Node;
	typedef _RBTreeIterator<K, V> iterator;

	RBTree()
		:_header(new Node)
	{
		_header->_left = _header->_right = _header;
	}

	iterator begin()
	{
		//����һ������������
		return iterator(_header->_left);
	}

	iterator end()
	{
		return iterator(_header);
	}

	iterator rbegin()
	{
		return iterator(_header->_right);
	}

	pair<iterator, bool> insert(const pair<K, V>& kv)
	{
		//1.�������Ĳ���
		//a.����
		if (_header->_parent == nullptr)
		{
			//�������ڵ�
			Node* root = new Node(kv);
			//���ڵ���ɫΪ��ɫ
			root->_color = BLACK;

			_header->_parent = root;
			root->_parent = _header;
			_header->_left = _header->_right = root;
			return make_pair(iterator(root), true);
		}
		//b.�ǿ���
		Node* parent = nullptr;
		//�Ӹ��ڵ㿪ʼ����
		Node* cur = _header->_parent;
		while (cur)
		{
			parent = cur;
			//ͨ����ֵ�Ƚ�
			if (cur->_kv.first > kv.first)
				cur = cur->_left;
			else if (cur->_kv.first < kv.first)
				cur = cur->_right;
			else
				return make_pair(iterator(cur), false);
		}
		//�²���Ľڵ���ɫΪ��ɫ
		cur = new Node(kv);
		Node* node = cur;
		if (parent->_kv.first > cur->_kv.first)
			parent->_left = cur;
		else
			parent->_right = cur;
		cur->_parent = parent;	
		//2.������ɫ/��ת
		while (cur != _header->_parent && cur->_parent->_color == RED)
		{
			Node* parent = cur->_parent;
			Node* grandfather = parent->_parent;
			if (grandfather->_left == parent)
			{
				Node* uncle = grandfather->_right;

				//uncle ���ڣ� ��Ϊ��
				if (uncle && uncle->_color == RED)
				{
					//�޸�parent, uncle��ɫ
					parent->_color = uncle->_color = BLACK;
					//�޸�grandfather
					grandfather->_color = RED;
					//��������
					cur = grandfather;
				}
				else
				{
					//uncle�����ڣ����� uncle������Ϊ��
					//1. ��ת
					//�ж��Ƿ�Ϊ˫��
					if (cur == parent->_right)
					{
						RotateL(parent);
						swap(cur, parent);
						//�˻�������
					}
					//cur, parent������ߣ� �ҵ���
					RotateR(grandfather);

					//2. �޸���ɫ
					parent->_color = BLACK;
					grandfather->_color = RED;

					//3. ����
					break;
				}
			}
			else
			{
				Node* uncle = grandfather->_left;

				//uncle ������Ϊ��
				if (uncle && uncle->_color == RED)
				{
					parent->_color = uncle->_color = BLACK;
					grandfather->_color = RED;
					cur = grandfather;
				}
				else
				{
					//uncle ������ ���� ������Ϊ��
					//�ж��Ƿ����˫��
					if (cur == parent->_left)
					{
						RotateR(parent);
						swap(parent, cur);
					}
					RotateL(grandfather);
					grandfather->_color = RED;
					parent->_color = BLACK;
					break;
				}
			}
		}

		//���ڵ�ʼ���Ǻ�ɫ
		_header->_parent->_color = BLACK;
		//����header�����ң�
		//header->_leftʼ��ָ������ڵ�
		//header->_rightʼ��ָ�����ҽڵ�
		_header->_left = leftMost();
		_header->_right = rightMost();
		//return true;
		return make_pair(iterator(node), true);
	}
	void RotateR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;

		subL->_right = parent;
		parent->_left = subLR;
		if (subLR)
			subLR->_parent = parent;

		//�ж�parent�Ƿ�Ϊ���ڵ�
		if (parent == _header->_parent)
		{
			//subL��Ϊ�µĸ��ڵ�
			_header->_parent = subL;
			subL->_parent = _header;
		}
		else
		{
			Node* g = parent->_parent;
			if (g->_left == parent)
				g->_left = subL;
			else
				g->_right = subL;
			subL->_parent = g;
		}
		parent->_parent = subL;
	}

	void RotateL(Node* parent)
	{
		//parent, subRL, subR
		Node* subR = parent->_right;
		Node* subRL = subR->_left;

		subR->_left = parent;
		parent->_right = subRL;
		if (subRL)
			subRL->_parent = parent;
		if (parent == _header->_parent)
		{
			_header->_parent = subR;
			subR->_parent = _header;
		}
		else
		{
			Node* g = parent->_parent;
			if (g->_left == parent)
				g->_left = subR;
			else
				g->_right = subR;
			subR->_parent = g;
		}
		parent->_parent = subR;
	}

	Node* leftMost()
	{
		Node* cur = _header->_parent;
		while (cur && cur->_left)
			cur = cur->_left;
		return cur;
	}

	Node* rightMost()
	{
		Node* cur = _header->_parent;
		while (cur && cur->_right)
			cur = cur->_right;
		return cur;
	}

	void _inorder(Node* root)
	{
		if (root)
		{
			_inorder(root->_left);
			cout << root->_kv.first << " ";
			_inorder(root->_right);
		}
	}

	void inorder()
	{
		_inorder(_header->_parent);
		cout << endl;
	}

	bool isRBTree()
	{
		Node* root = _header->_parent;
		if (root == NULL)
			return false;
		if (root->_color == RED)
		{
			cout << "�����Ǻ�ɫ" << endl;
			return false;
		}
		//����һ���ο�·���ϵĺ�ɫ�ڵ����
		Node* cur = root;
		int blackCount = 0;
		while (cur)
		{
			if (cur->_color == BLACK)
				++blackCount;
			cur = cur->_left;
		}
		int k = 0;
		return _isRBTree(root, k, blackCount);
	}

	bool _isRBTree(Node* root, int k, int blackCount)
	{
		//ÿ��·����ɫ�ڵ�����Ƿ���ͬ
		if (root == nullptr)
		{
			if (k == blackCount)
				return true;
			cout << "��ɫ��������ͬ" << endl;
			return false;
		}
		//�鿴��ǰ�ڵ��Ƿ�Ϊ��ɫ
		if (root->_color == BLACK)
			++k;
		//��ɫ�Ƿ�����
		if (root->_parent&&root->_color == RED&&root->_parent->_color == RED)
		{
			cout << "��ɫ����" << endl;
			return false;
		}
		return _isRBTree(root->_left, k, blackCount) && _isRBTree(root->_right, k, blackCount);
	}

private:
	Node* _header;
};

//void test()
//{
//	RBTree<int, int> rbtree;
//	rbtree.insert(make_pair(20, 20));
//	rbtree.insert(make_pair(10, 10));
//	rbtree.insert(make_pair(30, 30));
//	rbtree.insert(make_pair(5, 5));
//	rbtree.insert(make_pair(15, 15));
//	rbtree.insert(make_pair(25, 25));
//	rbtree.insert(make_pair(35, 35));
//	rbtree.insert(make_pair(2, 2));
//	rbtree.insert(make_pair(8, 8));
//	rbtree.insert(make_pair(1, 10));
//	RBTree<int, int>::iterator it = rbtree.rbegin();
//	while (it != rbtree.end())
//	{
//		cout << it->first << " ";
//		--it;
//	}
//	cout << endl;
//}

//void test()
//{
//	RBTree<int, int> rbtree;
//	rbtree.insert(make_pair(20, 20));
//	rbtree.insert(make_pair(10, 10));
//	rbtree.insert(make_pair(30, 30));
//	rbtree.insert(make_pair(5, 5));
//	rbtree.insert(make_pair(15, 15));
//	rbtree.insert(make_pair(25, 25));
//	rbtree.insert(make_pair(35, 35));
//	rbtree.insert(make_pair(2, 2));
//	rbtree.insert(make_pair(8, 8));
//	rbtree.insert(make_pair(1, 10));
//	rbtree.insert(make_pair(3, 1));
//	rbtree.insert(make_pair(100, 1));
//	rbtree.insert(make_pair(40, 1));
//	rbtree.insert(make_pair(7, 1));
//	rbtree.insert(make_pair(9, 1));
//
//	rbtree.inorder();
//	cout << rbtree.isRBTree() << endl;
//}

//void test()
//{
//	int n;
//	cout << "���ݸ����� " << endl;
//	cin >> n;
//	RBTree<int, int> rbt;
//	srand(time(nullptr));
//	for (int i = 0; i < n; ++i)
//	{
//		int num = rand();
//		rbt.insert(make_pair(num, num));
//	}
//	rbt.inorder();
//	cout << rbt.isRBTree() << endl;
//}

//int main()
//{
//	test();
//	system("pause");
//	return 0;
//}