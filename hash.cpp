#include<utility>
#include<vector>
#include<iostream>
using namespace std;

////////开散列
//哈希表中存放节点指针
//每一个哈希表的位置都是一个单链表
//所有产生相同哈希位置的数据都会存入同一个单链表中

template<class K>
struct KeyOfValue
{
	const K& operator()(const K& data)
	{
		return data;
	}
};

template<class V>
struct HashNode
{
	V _data;
	HashNode<V>* _next;
	HashNode(const V& data)
		:_data(data)
		, _next(nullptr)
	{}
};

struct strHFun
{
	size_t operator()(const string& str)
	{
		size_t hash = 0;
		for (auto ch : str)
		{
			hash = hash * 131 + ch;
		}
		return hash;
	}
};

template<class K>
struct HFun
{
	const K& operator()(const K& data)
	{
		return data;
	}
};

//string特化
template<>
struct HFun<string>
{
	size_t operator()(const string& str)
	{
		size_t hash = 0;
		for (auto ch : str)
		{
			hash = hash * 131 + ch;
		}
		return hash;
	}
};

//前置声明
template<class K, class V, class keyOfValue, class HFun>
class HashTable;

template<class K, class V, class keyOfValue, class HFun>
struct _HashIterator
{
	typedef HashNode<V> Node;
	typedef _HashIterator<K, V, keyOfValue, HFun> self;
	typedef HashTable<K, V, keyOfValue, HFun> hTable;
	//封装节点
	Node* _node;
	//哈希表指针
	hTable* _pht;

	_HashIterator(Node* node, hTable* pht)
		:_node(node)
		, _pht(pht)
	{}

	//*, ->
	V& operator* ()
	{
		return _node->_data;
	}

	V& operator->()
	{
		return &_node->_data;
	}
	//!=
	bool operator!=(const self& it)
	{
		return _node != it._node;
	}
	//++
	self& operator++()
	{
		//判断next是否为空
		if (_node->_next)
		{
			_node = _node->_next;
		}
		else
		{
			//找到下一个非空单链表头结点
			//首先计算当前节点在哈希表中的位置
			keyOfValue kov;
			//哈希函数：把key转换成对用的一个数值
			HFun hfun;
			size_t idx = hfun(kov(_node->_data)) % _pht->_ht.size();
			++idx;
			for (; idx < _pht->_ht.size(); ++idx)
			{
				if (_pht->_ht[idx])
				{
					_node = _pht->_ht[idx];
					break;
				}
			}
			if (idx >= _pht->_ht.size())
				_node = nullptr;
		}
		return *this;
	}
};



//哈希表
template<class K, class V, class keyOfValue, class HFun>
class HashTable
{
public:
	typedef HashNode<V> Node;
	typedef _HashIterator<K, V, keyOfValue, HFun> iterator;

	//友元类
	template<class K, class V, class keyOfValue, class HFun>
	friend struct _HashIterator;

	HashTable(size_t n = 10)
	{
		_ht.resize(n);
	}

	iterator begin()
	{
		for (int i = 0; i < _ht.size(); ++i)
		{
			if (_ht[i])
				return iterator(_ht[i], this);
		}
		return iterator(nullptr, this);
	}

	iterator end()
	{
		return iterator(nullptr, this);
	}

	pair<iterator, bool> insert(const V& data)
	{
		//检查容量
		checkCapacity();

		keyOfValue kov;
		HFun hfun;
		//计算哈希位置
		size_t idx = hfun(kov(data)) % _ht.size();

		//判断当哈希桶中是否存在重复的元素
		Node* cur = _ht[idx];
		while (cur)
		{
			Node* next = cur->_next;
			if (hfun(kov(cur->_data)) == hfun(kov(data)))
				return make_pair(iterator(cur, this), false);
			cur = cur->_next;
		}
		//单链表头插
		cur = new Node(data);
		cur->_next = _ht[idx];
		_ht[idx] = cur;
		++_size;
		return make_pair(iterator(cur, this), true);
	}

	void checkCapacity()
	{
		if (_size == _ht.size())
		{
			//负载因子为1，增容
			int newC = _ht.size() == 0 ? 10 : 2 * _ht.size();
			//创建新的哈希表
			vector<Node*> newHt;
			newHt.resize(newC);
			keyOfValue kov;
			HFun hfun;
			//遍历旧表
			for (int i = 0; i < _ht.size(); i++)
			{
				//遍历当前哈希桶中的每一个元素
				Node* cur = _ht[i];
				while (cur)
				{
					Node* next = cur->_next;
					//计算当前节点的数据在新表中的位置
					int idx = hfun(kov(cur->_data)) % newHt.size();

					//头插
					cur->_next = newHt[idx];
					newHt[idx] = cur;

					cur = next;
				}
				_ht[i] = nullptr;
			}

			//旧表新表交换
			swap(_ht, newHt);
		}
	}

	Node* find(const K& key)
	{
		KeyOfValue kov;
		HFun hfun;
		//计算位置
		int idx = key%_ht.size();
		Node* cur = _ht[idx];
		while (cur)
		{
			//按照key值进行比较
			if (hfun(kov(cur->_data)) == key)
				return cur;
			cur = cur->_next;
		}
		return nullptr;
	}

	bool erase(const K& key)
	{
		int idx = key%_ht.size();
		Node* cur = _ht[idx];
		Node* prev = nullptr;
		KeyOfValue kov;
		HFun hfun;
		while (cur)
		{
			if (hfun(kov(cur->_data)) == key)
			{
				//删除
				//判断是否为头结点
				if (cur == _ht[idx])
					_ht[idx] = cur->_next;
				else
					prev->_next = cur->_next;

				delete cur;
				--_size;
				return true;
			}
			else
			{
				prev = cur;
				cur = cur->_next;
			}
		}
		return false;
	}

	//void checkCapacity()
	//{
	//	if (_size == _ht.size())
	//	{
	//		//负载因子为1，增容
	//		int newC = _ht.size() == 0 ? 10 : 2 * _ht.size();
	//		//创建新的哈希表
	//		HashTable<K, V, keyOfValue> newHt(newC);
	//		//遍历旧表
	//		for (int i = 0; i < _ht.size(); i++)
	//		{
	//			//遍历当前哈希桶中的每一个元素
	//			Node* cur = _ht[i];
	//			while (cur)
	//			{
	//				Node* next = cur;
	//				//在新表中创建节点，释放旧表中的节点，效率低
	//				newHt.insert(cur->_data);//new 节点
	//				//释放当前节点
	//				delete cur;
	//				cur = next;
	//			}
	//			_ht[i] = nullptr;
	//		}

	//		//旧表新表交换
	//		swap(_ht, newHt._ht);
	//	}
	//}
	
private:
	vector<Node*> _ht;
	size_t _size = 0;
};

template<class K, class V, class HashFun = HFun<K>>
class UnordererMap
{
	struct MapKeyOfValue
	{
		const K& operator()(const pair<K, V>& data)
		{
			return data.first;
		}
	};
public:
	typedef typename HashTable<K, pair<K, V>, MapKeyOfValue, HashFun>::iterator iterator;

	V& operator[](const K& key)
	{
		pair<iterator, bool> ret = insert(make_pair(key, V()));
		return ret.first->second;
	}

	pair<iterator, bool> insert(const pair<K, V>& data)
	{
		return _ht.insert(data);
	}

	iterator begin()
	{
		return _ht.begin();
	}

	iterator end()
	{
		return _ht.end();
	}
private:
	HashTable<K, pair<K, V>, MapKeyOfValue, HashFun> _ht;
};

template <class K, class HashFun = HFun<K>>
class UnonderedSet
{
	struct SetKeyOfValue
	{
		const K& operator()(const K& data)
		{
			return data;
		}
	};
public:
	typedef typename HashTable<K, K, SetKeyOfValue, HashFun>::iterator iterator;

	pair<iterator, bool> insert(const K& key)
	{
		return _ht.insert(key);
	}
	iterator begin()
	{
		return _ht.begin();
	}
	iterator end()
	{
		return _ht.end();
	}
private:
	HashTable<K, K, SetKeyOfValue, HashFun> _ht;
};

void test()
{
	UnonderedSet<string> s;
	//非数值数据->数据->哈希位置
	s.insert("abc");


	/*s.insert(10);
	s.insert(1);
	s.insert(4);
	s.insert(9);
	s.insert(13);
	s.insert(6);
	UnonderedSet<int>::iterator it = s.begin();
	while (it != s.end())
	{
		cout << *it << endl;
		++it;
	}*/

}
int main()
{
	test();
	system("pause");
	return 0;
}








/////////闭散列：线性探测
//enum State
//{
//	EMPTY,
//	EXIST,
//	DELETE
//};
//
//template<class K, class V>
//struct HashNode
//{
//	pair<K, V> _kv = pair<K,V>();
//	State _state = EMPTY;
//};
//
//template<class K, class V>
//class HashTable
//{
//public:
//	typedef HashNode<K, V> Node;
//	HashTable(size_t n=5)
//		:_size(0)
//	{
//		_ht.resize(n);
//	}
//	//插入
//	bool insert(const pair<K, V>&  kv)
//	{
//		//检查容量
//		checkCapacity();
//		//通过哈希函数计算位置
//		int idx = kv.first%_ht.size();
//		//判断当前位置是否为有效数据
//		//如果为有效数据，向后搜索
//		while (_ht[idx]._state == EXIST)
//		{
//			//判断键值是否存在
//			//如果当前状态为存在，表示数据有效，查看当前数据的键值是否存在
//			if (_ht[idx]._state == EXIST && _ht[idx]._kv.first == kv.first)
//			{
//				return false;
//			}
//			++idx;
//			//判断是否越界
//			if (idx == _ht.size())
//				idx = 0;
//		}
//		//如果不是有效数据，空位置或删除的位置，直接插入
//		_ht[idx]._kv = kv;
//		_ht[idx]._state = EXIST;
//		++_size;
//		return true;
//	}
//
//	void checkCapacity()
//	{
//		//负载因子：元素个数 / 空间的大小
//		//线性探测中，负载因子一定小于1，越接近1，哈希冲突概率越大
//		//一般是小于0.7
//		if (_ht.size() == 0 || _size * 10 / _ht.size() >= 7)
//		{
//			//扩容
//			int newC = _ht.size() == 0 ? 5 : 2 * _ht.size();
//			HashTable<K, V> newHT(newC);
//			//重新插入：空间发生变化，数据的位置可能发生变化
//			//遍历旧表中的元素，把有效元素存入新表
//			for (int i = 0; i < _ht.size(); i++)
//			{
//				if (_ht[i]._state == EXIST)
//					newHT.insert(_ht[i]._kv);
//			}
//
//			//交换新表内容
//			swap(_ht, newHT._ht);
//		}
//	}
//
//	//搜索
//	Node* find(const K& key)
//	{
//		//计算位置
//		int idx = key%_ht.size();
//		while (_ht[idx]._state != EMPTY)
//		{
//			//判断数据是否有效
//			if (_ht[idx]._state==EXIST && _ht[idx]._kv.first==key)
//				return &_ht[idx];
//			++idx;
//			if (idx == _ht.size())
//				idx = 0;
//		}
//		return nullptr;
//	}
//
//	//删除
//	bool erase(const K& key)
//	{
//		Node* idx = find(key);
//		if (idx)
//		{
//			//假删除
//			idx._state = DELETE;
//			--_size;
//			return true;
//		}
//		return false;
//	}
//
//private:
//	vector<Node> _ht;
//	size_t _size;//表示实际元素的个数
//};
//
//void test()
//{
//	HashTable<int, int> ht;
//	ht.insert(make_pair(5, 5));
//	ht.insert(make_pair(10, 10));
//	ht.insert(make_pair(15, 15));
//
//}

//int main()
//{
//	test();
//	system("pause");
//	return 0;
//}