#include <time.h>
#include <iostream>
#include <utility>
#include <iostream>
using namespace std;

//��ɫ��ö��
enum COLOR
{
	BLACK,
	RED
};
//�ڵ�ֻ���value
template <class V>
struct RBNode
{
	RBNode<V>* _parent;
	RBNode<V>* _left;
	RBNode<V>* _right;
	//����Ϊvalue
	V _data;
	//�ڵ����ɫ
	//bool _color;  // STL��ʵ��
	COLOR _color;

	//�ڵ���ɫĬ��Ϊ��ɫ
	RBNode(const V& data = V())
		:_parent(nullptr)
		, _left(nullptr)
		, _right(nullptr)
		, _data(data)
		, _color(RED)
	{}
};

//������������� ��ԭ��ָ�룬��װ�ڵ㣬
//������Ϊ����
template <class V>
struct _RBTreeIterator
{
	typedef RBNode<V> Node;
	typedef _RBTreeIterator<V> Self;

	//��װNode
	Node* _node;
	_RBTreeIterator(Node* node)
		:_node(node)
	{}

	V& operator*()
	{
		//��ȡ�ڵ��е�����
		return _node->_data;
	}

	V* operator->()
	{
		//��ȡ�ڵ������ݵ�ָ��
		return &_node->_data;
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

//K: ��ֵ key
//V: ���ݣ� key,  key-value
//KeyOfValue: ��ȡvalue��Ӧ��key
template <class K, class V, class KeyOfValue>
class RBTree
{
public:
	typedef RBNode<V> Node;
	typedef _RBTreeIterator<V> iterator;
	RBTree()
		:_header(new Node)
	{
		//��ͷ�Ŀյĺ����
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

	pair<iterator, bool> insert(const V& data)
	{
		//1. �������Ĳ���
		//a. ����
		if (_header->_parent == nullptr)
		{
			//�������ڵ�
			Node* root = new Node(data);
			//���ڵ���ɫΪ��ɫ
			root->_color = BLACK;

			_header->_parent = root;
			root->_parent = _header;

			_header->_left = _header->_right = root;
			//return true;
			return make_pair(iterator(root), true);
		}
		//b. �ǿ���
		Node* parent = nullptr;
		//�Ӹ��ڵ㿪ʼ����
		Node* cur = _header->_parent;
		//����һ���º�������KeyOfValue
		KeyOfValue kov;
		while (cur)
		{
			parent = cur;
			//ͨ����ֵ�Ƚ�
			if (kov(cur->_data) > kov(data))
				cur = cur->_left;
			else if (kov(cur->_data) < kov(data))
				cur = cur->_right;
			else
				//��ֵ�ظ�������ʧ��
				//return false;
				return make_pair(iterator(cur), false);
		}
		//�²���ڵ����ɫΪ��ɫ
		cur = new Node(data);
		Node* node = cur;
		if (kov(parent->_data) > kov(cur->_data))
			parent->_left = cur;
		else
			parent->_right = cur;
		cur->_parent = parent;

		//2. ������ɫ/��ת
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

	/*void _inorder(Node* root)
	{
	if (root)
	{
	_inorder(root->_left);
	cout << root->_kv.first << " ";
	_inorder(root->_right);
	}
	}*/

	/*void inorder()
	{
	_inorder(_header->_parent);
	cout << endl;
	}*/

	//�������
	// 1. ��Ϊ��ɫ
	// 2. ��ɫ��������
	// 3. ÿ��·����ɫ�ڵ������ͬ
	bool isRBtree()
	{
		Node* root = _header->_parent;
		if (root == NULL)
			return true;
		//���Ǻ�ɫ��
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
		return _isRBtree(root, k, blackCount);
	}

	bool _isRBtree(Node* root, int k, int blackCount)
	{
		//ÿ��·����ɫ�ڵ�����Ƿ���ͬ
		if (root == nullptr)
		{
			if (k == blackCount)
				return true;
			cout << "��ɫ������ͬ" << endl;
			return false;
		}
		//�鿴��ǰ�ڵ��Ƿ�Ϊ��ɫ�ڵ�
		if (root->_color == BLACK)
			++k;

		//��ɫ�Ƿ�����
		if (root->_parent && root->_color == RED && root->_parent->_color == RED)
		{
			cout << "��ɫ����" << endl;
			return false;
		}

		return _isRBtree(root->_left, k, blackCount) && _isRBtree(root->_right, k, blackCount);
	}

private:
	//����һ��ͷ���
	Node* _header;
};

template <class K, class V>
class Map
{
	struct MapKeyOfValue
	{
		const K& operator()(const pair<K, V>& data)
		{
			return data.first;
		}
	};
public:
	typedef typename RBTree<K, pair<K, V>, MapKeyOfValue>::iterator iterator;
	iterator begin()
	{
		return _rbt.begin();
	}

	iterator end()
	{
		return _rbt.end();
	}

	pair<iterator, bool> insert(const pair<K, V>& data)
	{
		return _rbt.insert(data);
	}

	V& operator[](const K& key)
	{
		//1. ���� key, V()
		pair<iterator, bool> ret = insert(make_pair(key, V()));
		return ret.first->second;
	}
private:
	RBTree<K, pair<K, V>, MapKeyOfValue> _rbt;
};

template <class K>
class Set
{
	struct SetKeyOfValue
	{
		const K& operator()(const K& data)
		{
			return data;
		}
	};
public:
	typedef typename RBTree<K, K, SetKeyOfValue>::iterator iterator;

	iterator begin()
	{
		return _rbt.begin();
	}
	iterator end()
	{
		return _rbt.end();
	}

	pair<iterator, bool> insert(const K& key)
	{
		return _rbt.insert(key);
	}
private:
	RBTree<K, K, SetKeyOfValue> _rbt;
};

void test()
{
	Set<int> s;
	s.insert(10);
	s.insert(1);
	s.insert(5);
	s.insert(3);
	s.insert(2);

	Set<int>::iterator it = s.begin();
	while (it != s.end())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;

	cout << "for: " << endl;
	for (const auto& k : s)
	{
		cout << k << " ";
	}
	cout << endl;
}

//void test()
//{
//	Map<int, int> mp;
//	
//	mp[10] = 10;
//	mp[10] = 5;
//	mp[1] = 1;
//	mp[7] = 7;
//	mp[3] = 3;
//	mp[6] = 6;
//	mp[2] = 2;
//	mp[2] = 200;
//
//	Map<int, int>::iterator it = mp.begin();
//	while (it != mp.end())
//	{
//		cout << it->first << " " << it->second <<endl;
//		++it;
//	}
//	//cout << endl;
//	cout << "for: " << endl;
//	for (const auto& p : mp)
//		cout << p.first << " " << p.second << endl;
//}

//void test()
//{
//	Map<int, int> mp;
//	mp.insert(make_pair(1, 1));
//	mp.insert(make_pair(10, 1));
//	mp.insert(make_pair(15, 1));
//	mp.insert(make_pair(9, 1));
//	mp.insert(make_pair(0, 1));
//	mp.insert(make_pair(3, 1));
//	mp.insert(make_pair(2, 1));
//
//	Map<int, int>::iterator it = mp.begin();
//	while (it != mp.end())
//	{
//		cout << it->first << " ";
//		++it;
//	}
//	cout << endl;
//}

int main()
{
	test();
	system("pause");
	return 0;
}