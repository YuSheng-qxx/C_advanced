#include<iostream>
#include<memory>
#include<mutex>
#include<thread>
using namespace std;

//懒汉模式---多线程
class Singleton
{
public:
	//static公有方法创建对象:第一次调用时创建对象
	static Singleton* getOBJ()
	{
		//提高效率
		if (_ptr == nullptr)
		{
			_mtx.lock();
			//创建对象:第一次调用时创建对象
			//保证单例
			if (_ptr == nullptr)
			{
				_ptr = new Singleton;
			}
			_mtx.unlock();
		}
		return _ptr;
	}

	class GarbageGC
	{
		~GarbageGC()
		{
			if (_ptr)
				delete _ptr;
		}
	};

private:
	//构造函数私有
	Singleton()
	{
		cout << "Singleton()" << endl;
	}

	//防拷贝
	Singleton(const Singleton&) = delete;

	static Singleton* _ptr;
	static mutex _mtx;
	static GarbageGC _gc;
};

Singleton* Singleton::_ptr = nullptr;
mutex Singleton::_mtx;
Singleton::GarbageGC Singleton::_gc;

void fun(int n)
{
	for (int i = 0; i < n; i++)
	{
		Singleton* ptr = Singleton::getOBJ();
	}
}

void test()
{
	int n;
	cin >> n;
	thread t1(fun, n);
	thread t2(fun, n);
	thread t3(fun, n);
	thread t4(fun, n);
	thread t5(fun, n);

	t1.join();
	t2.join();
	t3.join();
	t4.join();
	t5.join();

}



////懒汉模式---单线程
//class Singleton
//{
//public:
//	//static公有方法创建对象:第一次调用时创建对象
//	static Singleton* getOBJ()
//	{
//		//创建对象:第一次使用时创建
//		if (_ptr == nullptr)
//		{
//			_ptr = new Singleton;
//		}
//		return _ptr;
//	}
//private:
//	//构造函数私有
//	Singleton()
//	{
//		cout << "Singleton()" << endl;
//	}
//
//	//防拷贝
//	Singleton(const Singleton&) = delete;
//
//	static Singleton* _ptr;
//};
//
//Singleton* Singleton::_ptr = nullptr;
//
//void test()
//{
//	Singleton* ptr = Singleton::getOBJ();
//	cout << ptr << endl;
//	ptr = Singleton::getOBJ();
//	cout << ptr << endl;
//	ptr = Singleton::getOBJ();
//	cout << ptr << endl;
//	ptr = Singleton::getOBJ();
//	cout << ptr << endl;
//	ptr = Singleton::getOBJ();
//	cout << ptr << endl;
//}





////饿汉模式
//class Singleton
//{
//public:
//	//公有的static方法
//	static Singleton& getOBJ()
//	{
//		return _singleton;
//	}
//private:
//	//构造函数私有化
//	Singleton()
//	{}
//
//	//防拷贝
//	Singleton(const Singleton&) = delete;
//
//	//static成员
//	static Singleton _singleton;
//};
//
//Singleton Singleton::_singleton;
//
//void test()
//{
//	Singleton& ref = Singleton::getOBJ();
//	cout << &ref << endl;
//} 


















//只能在栈上创建对象
//class StackOnly
//{
//	//重定义operator
//	void* operator new(size_t n) = delete;
//	void operator delete(void* ptr) = delete;
//};
//
//void test()
//{
//	StackOnly so;
//	//StackOnly* ptr = new StackOnly;
//}



//只能在栈上创建对象
//class StackOnly
//{
//public:
//	//公有的方法,在栈上创建对象
//	static StackOnly getOBJ()
//	{
//		StackOnly so;
//		return so;
//	}
//
//private:
//	//构造函数私有化
//	StackOnly()
//	{}
//};
//
//void test()
//{
//	//StackOnly* p = new StackOnly;
//	StackOnly so = StackOnly::getOBJ();
//}












//只能在堆上创建对象
//class HeapOnly
//{
//public:
//	//公有的方法，创建对象
//	static HeapOnly* getOBJ()
//	{
//		//堆上创建对象
//		return new HeapOnly;
//	}
//private:
//	//构造函数私有化
//	HeapOnly()
//	{}
//
//	//防拷贝
//	//拷贝构造私有化
//	HeapOnly(const HeapOnly& ho);
//	//或者直接定义成delete函数
//	HeapOnly(const HeapOnly& ho) = delete;
//};
//
//void test()
//{
//	//栈上的对象
//	//HeapOnly ho;
//
//	//堆上的对象
//	HeapOnly* ptr1 = HeapOnly::getOBJ();
//	HeapOnly* ptr2 = HeapOnly::getOBJ();
//
//	//栈上的对象
//	//HeapOnly copy(*ptr);
//
//	*ptr1 = *ptr2;
//}

int main()
{
	test();
	system("pause");
	return 0;
}