#include <time.h>
#include <iostream>
#include <utility>
#include <iostream>
using namespace std;

//颜色的枚举
enum COLOR
{
	BLACK,
	RED
};
//节点只存放value
template <class V>
struct RBNode
{
	RBNode<V>* _parent;
	RBNode<V>* _left;
	RBNode<V>* _right;
	//数据为value
	V _data;
	//节点的颜色
	//bool _color;  // STL的实现
	COLOR _color;

	//节点颜色默认为红色
	RBNode(const V& data = V())
		:_parent(nullptr)
		, _left(nullptr)
		, _right(nullptr)
		, _data(data)
		, _color(RED)
	{}
};

//红黑树迭代器： 非原生指针，封装节点，
//迭代器为对象
template <class V>
struct _RBTreeIterator
{
	typedef RBNode<V> Node;
	typedef _RBTreeIterator<V> Self;

	//封装Node
	Node* _node;
	_RBTreeIterator(Node* node)
		:_node(node)
	{}

	V& operator*()
	{
		//获取节点中的数据
		return _node->_data;
	}

	V* operator->()
	{
		//获取节点中数据的指针
		return &_node->_data;
	}

	bool operator!=(const Self& it)
	{
		return _node != it._node;
	}
	//中序移动： 左跟右
	Self& operator++()
	{
		//判断是否有右子树
		if (_node->_right)
		{
			//下一个要访问的节点： 右子树的最左节点
			_node = _node->_right;
			while (_node->_left)
				_node = _node->_left;
		}
		else
		{
			//有子树不存在，
			//下一个要访问的节点： 父节点--> 次父节点的孩子节点不是它的右
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

	//右根左
	Self& operator--()
	{
		//左子树存在， 找左子树最右节点
		if (_node->_left)
		{
			_node = _node->_left;
			while (_node->_right)
				_node = _node->_right;
		}
		else
		{
			//左子树不存在，找父节点： 它的孩子不是它的左
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

//K: 键值 key
//V: 数据： key,  key-value
//KeyOfValue: 获取value对应的key
template <class K, class V, class KeyOfValue>
class RBTree
{
public:
	typedef RBNode<V> Node;
	typedef _RBTreeIterator<V> iterator;
	RBTree()
		:_header(new Node)
	{
		//带头的空的红黑树
		_header->_left = _header->_right = _header;
	}

	iterator begin()
	{
		//创建一个迭代器对象
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
		//1. 搜索树的插入
		//a. 空树
		if (_header->_parent == nullptr)
		{
			//创建根节点
			Node* root = new Node(data);
			//根节点颜色为黑色
			root->_color = BLACK;

			_header->_parent = root;
			root->_parent = _header;

			_header->_left = _header->_right = root;
			//return true;
			return make_pair(iterator(root), true);
		}
		//b. 非空树
		Node* parent = nullptr;
		//从根节点开始搜索
		Node* cur = _header->_parent;
		//定义一个仿函数对象KeyOfValue
		KeyOfValue kov;
		while (cur)
		{
			parent = cur;
			//通过键值比较
			if (kov(cur->_data) > kov(data))
				cur = cur->_left;
			else if (kov(cur->_data) < kov(data))
				cur = cur->_right;
			else
				//键值重复，插入失败
				//return false;
				return make_pair(iterator(cur), false);
		}
		//新插入节点的颜色为红色
		cur = new Node(data);
		Node* node = cur;
		if (kov(parent->_data) > kov(cur->_data))
			parent->_left = cur;
		else
			parent->_right = cur;
		cur->_parent = parent;

		//2. 调整颜色/旋转
		while (cur != _header->_parent && cur->_parent->_color == RED)
		{
			Node* parent = cur->_parent;
			Node* grandfather = parent->_parent;
			if (grandfather->_left == parent)
			{
				Node* uncle = grandfather->_right;

				//uncle 存在， 且为红
				if (uncle && uncle->_color == RED)
				{
					//修改parent, uncle颜色
					parent->_color = uncle->_color = BLACK;
					//修改grandfather
					grandfather->_color = RED;
					//继续更新
					cur = grandfather;
				}
				else
				{
					//uncle不存在，或者 uncle存在且为黑
					//1. 旋转
					//判断是否为双旋
					if (cur == parent->_right)
					{
						RotateL(parent);
						swap(cur, parent);
						//退化到单旋
					}
					//cur, parent都在左边， 右单旋
					RotateR(grandfather);

					//2. 修改颜色
					parent->_color = BLACK;
					grandfather->_color = RED;

					//3. 结束
					break;
				}
			}
			else
			{
				Node* uncle = grandfather->_left;

				//uncle 存在且为红
				if (uncle && uncle->_color == RED)
				{
					parent->_color = uncle->_color = BLACK;
					grandfather->_color = RED;
					cur = grandfather;
				}
				else
				{
					//uncle 不存在 或者 存在且为黑
					//判断是否存在双旋
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

		//根节点始终是黑色
		_header->_parent->_color = BLACK;
		//更新header的左右，
		//header->_left始终指向最左节点
		//header->_right始终指向最右节点
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

		//判断parent是否为根节点
		if (parent == _header->_parent)
		{
			//subL作为新的根节点
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

	//红黑树：
	// 1. 根为黑色
	// 2. 红色不能连续
	// 3. 每条路径黑色节点个数相同
	bool isRBtree()
	{
		Node* root = _header->_parent;
		if (root == NULL)
			return true;
		//根是黑色的
		if (root->_color == RED)
		{
			cout << "根不是黑色" << endl;
			return false;
		}
		//计算一个参考路径上的黑色节点个数
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
		//每条路径黑色节点个数是否相同
		if (root == nullptr)
		{
			if (k == blackCount)
				return true;
			cout << "黑色个数不同" << endl;
			return false;
		}
		//查看当前节点是否为黑色节点
		if (root->_color == BLACK)
			++k;

		//红色是否连续
		if (root->_parent && root->_color == RED && root->_parent->_color == RED)
		{
			cout << "红色连续" << endl;
			return false;
		}

		return _isRBtree(root->_left, k, blackCount) && _isRBtree(root->_right, k, blackCount);
	}

private:
	//定义一个头结点
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
		//1. 插入 key, V()
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