//#include<iostream>
//#include<string>
//using namespace std;
//
//template<class T>
//class HashFunc
//{
//public:
//	size_t operator()(const T& val)
//	{
//		return val;
//	}
//};
//
//template<>
//class HashFunc<string>
//{
//public:
//	size_t operator()(const string& s)
//	{
//		const char* str = s.c_str();
//		unsigned int seed = 131; // 31 131 1313 13131 131313
//		unsigned int hash = 0;
//		while (*str)
//		{
//			hash = hash * seed + (*str++);
//		}
//		return hash;
//	}
//};
//
//template<class V>
//struct HashBucketNode
//{
//	HashBucketNode(const V& data)
//	: _pNext(nullptr), _data(data)
//	{}
//	HashBucketNode<V>* _pNext;
//	V _data;
//};
//
//// 本文所实现的哈希桶中key是唯一的
//template<class V, class HF = HashFunc<V>>
//class HashBucket
//{
//	typedef HashBucketNode<V> Node;
//	typedef Node* PNode;
//
//	typedef HashBucket<V, HF> Self;
//
//public:
//	HashBucket(size_t capacity)
//		: _table(GetNextPrime(capacity))
//		, _size(0)
//	{}
//
//	~HashBucket()
//	{
//		Clear();
//	}
//
//	// 哈希桶中的元素不能重复
//	Node* Insert(const V& data)
//	{
//		CheckCapacity();
//		size_t idx = HashFunc(data);
//		Node* pCur = _table[idx];
//		while (pCur)
//		{
//			if (pCur->_data == data)
//				return nullptr;
//			pCur = pCur->_pNext;
//		}
//		pCur = new Node(data);
//		pCur->_pNext = _table[idx];
//		_table[idx] = pCur;
//		++_size;
//		return pCur;
//	}
//
//	// 删除哈希桶中为data的元素(data不会重复)
//	bool Erase(const V& data)
//	{
//		size_t idx = HashFunc(data);
//		Node* pCur = _table[idx];
//		Node* pPre = nullptr;
//
//		while (pCur)
//		{
//			if (data == pCur->_data)
//			{
//				if (_table[idx] == pCur)
//				{
//					_table[idx] = pCur->_pNext;
//				}
//				else
//				{
//					pPre->_pNext = pCur->_pNext;
//				}
//				delete pCur;
//				--_size;
//				return true;
//			}
//			pPre = pCur;
//			pCur = pCur->_pNext;
//		}
//		return false;
//	}
//
//	Node* Find(const V& data)
//	{
//		size_t idx = HashFunc(data);
//		Node* pCur = _table[idx];
//		while (pCur)
//		{
//			if (data == pCur->_data)
//				return pCur;
//
//			pCur = pCur->_pNext;
//		}
//
//		return nullptr;
//	}
//
//	size_t Size()const
//	{
//		return _size;
//	}
//
//	bool Empty()const
//	{
//		return 0 == _size;
//	}
//
//	void Clear()
//	{
//		for (size_t i = 0; i < _table.capacity(); ++i)
//		{
//			Node* pCur = _table[i];
//
//			while (pCur)
//			{
//				_table[i] = pCur->_pNext;
//				delete pCur;
//				pCur = _table[i];
//			}
//		}
//		_size = 0;
//	}
//
//	size_t BucketCount()const
//	{
//		return _table.capacity();
//	}
//
//	void Swap(Self& ht)
//	{
//		_table.swap(ht._table);
//		swap(_size, ht._size);
//	}
//
//private:
//	size_t HashFunc(const V& data)
//	{
//		return HF()(data) % _table.capacity();
//	}
//
//	void CheckCapacity()
//	{
//		if (_size == _table.capacity())
//		{
//			Self ht(GetNextPrime(_size));
//
//			// 将旧哈希桶中的节点直接向新哈希桶中搬移
//			for (size_t i = 0; i < _table.capacity(); ++i)
//			{
//				Node* pCur = _table[i];
//				while (pCur)
//				{
//					// 将pCur节点从旧哈希桶搬移到新哈希桶
//					// 1. 将pCur节点从旧链表中删除
//					_table[i] = pCur->_pNext;
//
//					// 2. 将pCur节点插入到新链表中
//					size_t bucketNo = ht.HashFunc(pCur->_data);
//
//					// 3. 插入节点--->头插
//					pCur->_pNext = ht._table[bucketNo];
//					ht._table[bucketNo] = pCur;
//				}
//			}
//
//			this->Swap(ht);
//		}
//	}
//
//private:
//	vector<Node*> _table;
//	size_t _size;      // 哈希表中有效元素的个数
//};
//
//void test()
//{
//	HashBucket<int> _ht(8);
//	_ht.Insert(5);
//	_ht.Insert(10);
//	_ht.Insert(15);
//	_ht.Insert(4);
//	_ht.Insert(3);
//	_ht.Insert(18);
//	_ht.Insert(2);
//	cout << _ht.Size() << endl;
//	cout << _ht.Find(3) << endl;
//}
//
//int main()
//{
//	test();
//	system("pause");
//	return 0;
//}


//int main()
//{
//	int a[] = { 2, 4, 6, 8, 10 }, *p, **k;
//	p = a;
//	k = &p;
//	printf(" % d", *(p++));
//	printf(" % d\n", **k);
//	system("pause");
//}
//float func(float a, int b)
//{
//	float m = 1, n = 1;
//	int i;
//	for (i = 1; i <b; i++)
//	{
//		m *= a / i;
//		n += m;
//	} 
//	return n;
//}
//
//int main()
//{
//	cout<<func('a','b');
//	system("pause");
//	return 0;
//}
//int main()
//{
//	char *p = "abcdefgh", *r;
//	long *q;
//	q = (long*)p;
//	q++;
//	r = (char*)q;
//	printf("%s\n", r);
//	
//}

//int foo(int x, int y)
//{
//	if (x <= 0 || y <= 0)
//		return 1;
//	return 3 * foo(x - 6, y / 2);
//}
//int main()
//{
//	cout << foo(20, 13) << endl;
//	system("pause");
//	return 0;
//}

//class Base
//{
//public:
//	virtual void func1()
//	{
//		cout << "Base::func1()" << endl;
//	}
//
//	virtual void func2()
//	{
//		cout << "Base::func2()" << endl;
//	}
//
//	void func3()
//	{
//		cout << "Base::func3()" << endl;
//	}
//private:
//	int _b = 1;
//};
//
//class Derive :public Base
//{
//public:
//	virtual void func1()
//	{
//		cout << "Derive::func1()" << endl;
//	}
//private:
//	int _d = 2;
//};
//
//void test()
//{
//	Base b;
//	Derive d;
//}
//
//int main()
//{
//	test();
//	system("pause");
//	return 0;
//}

//class A
//{
//public:
//	//纯虚函数
//	virtual void func4() = 0;
//};
//class B:public A
//{
//public:
//	//重写父类中的纯虚函数
//	virtual void func4()
//	{
//		cout << "B::func4()" << endl;
//	}
//};

//class A
//{
//public:
//	//final修饰的虚函数不能在子类中被重写
//	//体现实现继承
//	virtual void func()final
//	{
//		cout << "A::func()" << endl;
//	}
//};
//class B :public A
//{
//public:
//	virtual void func()
//	{
//		cout << "B::func()" << endl;
//	}
//};


//class Person
//{
//public:
//	virtual ~Person()
//	{
//		cout << "~Person()" << endl;
//	}
//};
//class Student
//{
//public:
//	virtual ~Student()
//	{
//		cout << "~Student()" << endl;
//	}
//};

//抽象类：包含纯虚函数的类
//抽象类不能实例化对象：成员不完整
//class A
//{
//public:
//	//final修饰的虚函数不能在子类中被重写/继承
//	//体现实现继承
//	virtual void func()final
//	{
//		cout << "A::func()" << endl;
//	}
//
//	virtual void func2()
//	{
//		cout << "A::func2()" << endl;
//	}
//
//	//纯虚函数
//	virtual void func4() = 0;
//	
//
//	//析构尽量写成虚函数
//	virtual ~A()
//	{
//		cout << "~A()" << endl;
//	}
//};
//class B:public A
//{
//public:
//	//override：强制子类的函数必须重写父类的一个虚函数
//	virtual void func2()override
//	{
//		cout << "B::func3()" << endl;
//	}
//	/*virtual void func()
//	{
//		cout << "B::func()" << endl;
//	}*/
//
//	//重写父类中的纯虚函数
//	virtual void func4()
//	{
//		cout << "B::func4()" << endl;
//	}
//	virtual ~B()//重写父类的析构函数：底层函数名相同
//	{
//		cout << "~B()" << endl;
//	}
//};
////不实现抽象类中的纯虚函数的子类也是一个抽象类
//class C :public A
//{
//
//};
//void test()
//{
//	A* pa = new A;
//	B* pb = new B;
//	delete pa;
//	delete pb;
//	//切片:有内存泄露的风险：析构不是多态，如果子类对象中有资源申请，会导致只调用父类的析构，子类对象的资源不会释放
//	//多态：看对象->子类对象->子类析构
//	//父类指针/引用指向继承体系中的对象
//	A* pc = new B;
//	delete pc;
//
//	C* pd = new C;
//}
//int main()
//{
//	test();
//	system("pause");
//	return 0;
//}

//class A
//{};
//
//class B:public A
//{};
//
//class Person
//{
//public:
//	virtual void buyTicket()
//	{
//		cout << "普通票" << endl;
//		return new A();
//	}
//	virtual A& buyTicket()
//	{
//		cout << "普通票" << endl;
//		return A();
//	}
//};
//
//class Student :public Person
//{
//	//子类进行虚函数的重写
//	//子类重新定义一个和父类接口完全相同的函数：函数名、参数、返回值完全相同
//public:
//	virtual void buyTicket()
//	{
//		cout << "半票" << endl;
//		return new B();
//	}
//	virtual B& buyTicket()
//	{
//		cout << "半票" << endl;
//		return B();
//	}
//};
//
//void func(Person* p)
//{
//	p->buyTicket();
//}
//
//void test()
//{
//	Person p;
//	Student s;
//
//	/*Student* ps = &s;
//	Person* pp = &p;*/
//	/*ps->buyTicket();
//	pp->buyTicket();*/
//	func(&p);
//	func(&s);
//}


//class Car{
//protected:
//	string _colour = "白色"; // 颜色
//	string _num = "陕ABIT00"; // 车牌号
//};
//class BMW : public Car{
//public:
//	void Drive() { cout << "好开-操控" << endl; }
//};
//class Benz : public Car{
//public:
//	void Drive() { cout << "好坐-舒适" << endl; }
//};

//class Tire
//{
//protected:
//	string _brand = "Michelin";//品牌
//	size_t _size = 12;//尺寸
//};
//class Car
//{
//protected:
//	string _color = "白";//颜色
//	string _num = "陕AB102";//车牌
//	Tire _t;//轮胎
//};



//class A
//{
//public:
//	int _a;
//};
//class B : virtual public A
//{
//public:
//	int _b;
//};
//
//class C : virtual public A
//{
//public:
//	int _c;
//};
//
//class D :public B, public C
//{
//public:
//	int _d;
//};
//
//void test()
//{
//	D d;
//	d.B::_a = 1;
//	d._b = 2;
//	d.C::_a = 3;
//	d._c = 4;
//	d._d = 5;
//}
//
//int main()
//{
//	test();
//	system("pause");
//	return 0;
//}


//class A
//{
//public:
//	static int _i;
//};
//int A::_i = 10;
//class B :public A
//{};
//
//class C :public B,public A
//{};
//void test()
//{
//	A a;
//	B b;
//	C c;
//	int *ptr = &a._i;
//	ptr = &b._i;
//	ptr = &c._i;
//}




//class A
//{
//public:
//	A()
//	{
//		cout << "A()" << endl;
//	}
//	A(int a)
//		:_a(a)
//	{
//		cout << "A(int)" << endl;
//	}
//	A(const A& a)
//	{
//		cout << "A(const A& a)" << endl;
//	}
//	A& operator =(const A& a)
//	{
//		cout << "operator=(const A& )" << endl;
//		return *this;
//	}
//	~A()
//	{
//		cout << "~A" << endl;
//	}
//private:
//	int _a;
//};
//
//class B :public A
//{
//public:
//	B()
//		:A()
//	{
//		cout << "B()" << endl;
//	}
//
//	B(int a,int b)
//		:A(a)
//		, _b(b)
//	{}
//
//	B(const B& b)
//		:A(b)
//	{
//		cout << "B(const B& b)" << endl;
//	}
//
//	B& operator =(const B& b)
//	{
//		A::operator=(b);
//		cout << "operator=(const B& b)" << endl;
//		return *this;
//	}
//	
//	~B()
//	{
//		//A::~A();
//		cout << "~B" << endl;
//	}
//private:
//	int _b;
//};
//void test()
//{
//	B b1;
//	B b2 = b1;
//}


//class person
//{
//protected:
//	string _name = "peter"; // 姓名
//	int _age = 18; // 年龄
//};
//
//class student : public person
//{
//public:
//		int _stuid; // 学号
//};
//
//
//void test()
//{
//	student s;
//
//	person p = s;
//	person *pp = &s;
//	student* ps1 = (student*)pp;
//	ps1->_stuid = 10;
//
//	pp = &p;
//	student* ps2 = (student*)pp;
//	ps2->_stuid = 10;
//}

//int main()
//{
//	test();
//	system("pause");
//	return 0;
//}

//class A
//{
//public:
//	void fun()
//	{
//		cout << "fun()" << endl;
//	}
//};
//class B:public A
//{
//public:
//	void fun(int i)
//	{
//		A::fun();
//		cout << "fun(int i)->" << i << endl;
//	}
//};