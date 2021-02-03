#include<utility>
#include<vector>
#include<iostream>
using namespace std;

////////��ɢ��
//��ϣ���д�Žڵ�ָ��
//ÿһ����ϣ���λ�ö���һ��������
//���в�����ͬ��ϣλ�õ����ݶ������ͬһ����������

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

//string�ػ�
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

//ǰ������
template<class K, class V, class keyOfValue, class HFun>
class HashTable;

template<class K, class V, class keyOfValue, class HFun>
struct _HashIterator
{
	typedef HashNode<V> Node;
	typedef _HashIterator<K, V, keyOfValue, HFun> self;
	typedef HashTable<K, V, keyOfValue, HFun> hTable;
	//��װ�ڵ�
	Node* _node;
	//��ϣ��ָ��
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
		//�ж�next�Ƿ�Ϊ��
		if (_node->_next)
		{
			_node = _node->_next;
		}
		else
		{
			//�ҵ���һ���ǿյ�����ͷ���
			//���ȼ��㵱ǰ�ڵ��ڹ�ϣ���е�λ��
			keyOfValue kov;
			//��ϣ��������keyת���ɶ��õ�һ����ֵ
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



//��ϣ��
template<class K, class V, class keyOfValue, class HFun>
class HashTable
{
public:
	typedef HashNode<V> Node;
	typedef _HashIterator<K, V, keyOfValue, HFun> iterator;

	//��Ԫ��
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
		//�������
		checkCapacity();

		keyOfValue kov;
		HFun hfun;
		//�����ϣλ��
		size_t idx = hfun(kov(data)) % _ht.size();

		//�жϵ���ϣͰ���Ƿ�����ظ���Ԫ��
		Node* cur = _ht[idx];
		while (cur)
		{
			Node* next = cur->_next;
			if (hfun(kov(cur->_data)) == hfun(kov(data)))
				return make_pair(iterator(cur, this), false);
			cur = cur->_next;
		}
		//������ͷ��
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
			//��������Ϊ1������
			int newC = _ht.size() == 0 ? 10 : 2 * _ht.size();
			//�����µĹ�ϣ��
			vector<Node*> newHt;
			newHt.resize(newC);
			keyOfValue kov;
			HFun hfun;
			//�����ɱ�
			for (int i = 0; i < _ht.size(); i++)
			{
				//������ǰ��ϣͰ�е�ÿһ��Ԫ��
				Node* cur = _ht[i];
				while (cur)
				{
					Node* next = cur->_next;
					//���㵱ǰ�ڵ���������±��е�λ��
					int idx = hfun(kov(cur->_data)) % newHt.size();

					//ͷ��
					cur->_next = newHt[idx];
					newHt[idx] = cur;

					cur = next;
				}
				_ht[i] = nullptr;
			}

			//�ɱ��±���
			swap(_ht, newHt);
		}
	}

	Node* find(const K& key)
	{
		KeyOfValue kov;
		HFun hfun;
		//����λ��
		int idx = key%_ht.size();
		Node* cur = _ht[idx];
		while (cur)
		{
			//����keyֵ���бȽ�
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
				//ɾ��
				//�ж��Ƿ�Ϊͷ���
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
	//		//��������Ϊ1������
	//		int newC = _ht.size() == 0 ? 10 : 2 * _ht.size();
	//		//�����µĹ�ϣ��
	//		HashTable<K, V, keyOfValue> newHt(newC);
	//		//�����ɱ�
	//		for (int i = 0; i < _ht.size(); i++)
	//		{
	//			//������ǰ��ϣͰ�е�ÿһ��Ԫ��
	//			Node* cur = _ht[i];
	//			while (cur)
	//			{
	//				Node* next = cur;
	//				//���±��д����ڵ㣬�ͷžɱ��еĽڵ㣬Ч�ʵ�
	//				newHt.insert(cur->_data);//new �ڵ�
	//				//�ͷŵ�ǰ�ڵ�
	//				delete cur;
	//				cur = next;
	//			}
	//			_ht[i] = nullptr;
	//		}

	//		//�ɱ��±���
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
	//����ֵ����->����->��ϣλ��
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








/////////��ɢ�У�����̽��
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
//	//����
//	bool insert(const pair<K, V>&  kv)
//	{
//		//�������
//		checkCapacity();
//		//ͨ����ϣ��������λ��
//		int idx = kv.first%_ht.size();
//		//�жϵ�ǰλ���Ƿ�Ϊ��Ч����
//		//���Ϊ��Ч���ݣ��������
//		while (_ht[idx]._state == EXIST)
//		{
//			//�жϼ�ֵ�Ƿ����
//			//�����ǰ״̬Ϊ���ڣ���ʾ������Ч���鿴��ǰ���ݵļ�ֵ�Ƿ����
//			if (_ht[idx]._state == EXIST && _ht[idx]._kv.first == kv.first)
//			{
//				return false;
//			}
//			++idx;
//			//�ж��Ƿ�Խ��
//			if (idx == _ht.size())
//				idx = 0;
//		}
//		//���������Ч���ݣ���λ�û�ɾ����λ�ã�ֱ�Ӳ���
//		_ht[idx]._kv = kv;
//		_ht[idx]._state = EXIST;
//		++_size;
//		return true;
//	}
//
//	void checkCapacity()
//	{
//		//�������ӣ�Ԫ�ظ��� / �ռ�Ĵ�С
//		//����̽���У���������һ��С��1��Խ�ӽ�1����ϣ��ͻ����Խ��
//		//һ����С��0.7
//		if (_ht.size() == 0 || _size * 10 / _ht.size() >= 7)
//		{
//			//����
//			int newC = _ht.size() == 0 ? 5 : 2 * _ht.size();
//			HashTable<K, V> newHT(newC);
//			//���²��룺�ռ䷢���仯�����ݵ�λ�ÿ��ܷ����仯
//			//�����ɱ��е�Ԫ�أ�����ЧԪ�ش����±�
//			for (int i = 0; i < _ht.size(); i++)
//			{
//				if (_ht[i]._state == EXIST)
//					newHT.insert(_ht[i]._kv);
//			}
//
//			//�����±�����
//			swap(_ht, newHT._ht);
//		}
//	}
//
//	//����
//	Node* find(const K& key)
//	{
//		//����λ��
//		int idx = key%_ht.size();
//		while (_ht[idx]._state != EMPTY)
//		{
//			//�ж������Ƿ���Ч
//			if (_ht[idx]._state==EXIST && _ht[idx]._kv.first==key)
//				return &_ht[idx];
//			++idx;
//			if (idx == _ht.size())
//				idx = 0;
//		}
//		return nullptr;
//	}
//
//	//ɾ��
//	bool erase(const K& key)
//	{
//		Node* idx = find(key);
//		if (idx)
//		{
//			//��ɾ��
//			idx._state = DELETE;
//			--_size;
//			return true;
//		}
//		return false;
//	}
//
//private:
//	vector<Node> _ht;
//	size_t _size;//��ʾʵ��Ԫ�صĸ���
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