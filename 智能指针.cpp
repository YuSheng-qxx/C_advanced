#include<iostream>
#include<thread>
#include<memory>
#include<mutex>
using namespace std;

//struct Date
//{
//	int _y = 1;
//	int _m = 2;
//	int _d = 3; 
//
//	~Date()
//	{
//		cout << "~Date()" << endl;
//	}
//};



//shared_ptr：
//支持拷贝和赋值
//通过引用计数保证资源被正确且唯一的释放
//多线程中，通过对引用进行串行操作，保证计数更新正确
//每个资源都有自己独立的引用计数
//template <class T>
//class SharedPtr
//{
//public:
//	SharedPtr(T* ptr)
//		:_ptr(ptr)
//		, _count(new size_t(1))
//		, _mtx(new(mutex))
//	{}
//
//	SharedPtr(const SharedPtr<T>& sp)
//		:_ptr(sp._ptr)
//		, _count(sp._count)
//		, _mtx(sp._mtx)
//	{
//		//++(*_count);
//		addCount();
//	}
//
//	SharedPtr<T> operator=(const SharedPtr<T>& sp)
//	{
//		//if (this != sp)
//		//判断管理的资源是否为同一份资源
//		if (_ptr != sp._ptr)
//		{
//			//计数器--
//			//如果计数器为0，当前对象是最后一个管理资源的对象
//			//if (--(*_count) == 0)
//			if (subCount() == 0)
//			{
//				delete _ptr;
//				delete _count;
//				delete _mtx;
//			}
//
//			_ptr = sp._ptr;
//			_count = sp._count;
//			_mtx = sp._mtx;
//
//			//计数器累加
//
//			//++(*_count);
//			addCount();
//		}
//		return *this;
//	}
//
//	T& operator*()
//	{
//		return *_ptr;
//	}
//
//	T& operator->()
//	{
//		return _ptr;
//	}
//
//	~SharedPtr()
//	{
//		//if (--(*_count) == 0)
//		if (subCount() == 0)
//		{
//			delete _ptr;
//			delete _count;
//			delete _mtx;
//			_ptr = nullptr;
//			_count = nullptr;
//			_mtx = nullptr;
//		}
//	}
//
//	size_t addCount()
//	{
//		_mtx->lock();
//		++(*_count);
//		_mtx->unlock();
//		return *_count;
//	}
//
//	size_t subCount()
//	{
//		_mtx->lock();
//		--(*_count);
//		_mtx->unlock();
//		return *_count;
//	}
//
//private:
//	T* _ptr;
//	size_t* _count;
//	//每一份资源有一个独立的锁
//	mutex* _mtx;
//};
//
//void test()
//{
//	SharedPtr<Date> sp(new Date);
//	SharedPtr<Date> sp2(sp);
//	SharedPtr<Date> sp3(new Date);
//	sp3 = sp2;
//}

//void test()
//{
//	shared_ptr<Date> sp(new Date);
//	cout << sp.use_count() << endl;
//	shared_ptr<Date> sp2(sp);
//	cout << sp2.use_count() << endl;
//	cout << sp.use_count() << endl;
//
//	shared_ptr<Date> sp3(new Date);
//	cout << sp.use_count() << endl;
//	cout << sp2.use_count() << endl;
//	cout << sp3.use_count() << endl;
//
//	sp3 = sp;
//	sp3 = sp2; 
//	sp->_y = 2021;
//	sp2->_m = 1;
//	sp3->_d = 31;
//	cout << sp.use_count() << endl;
//	cout << sp2.use_count() << endl;
//	cout << sp3.use_count() << endl;
//}















//template <class T>
//class UniquePtr
//{
//public:
//	UniquePtr(T* ptr)
//		:_ptr(ptr)
//	{}
//
//	UniquePtr(const UniquePtr<T>& up) = delete;
//	UniquePtr<T>& operator=(const UniquePtr<T>& up) = delete;
//
//	~UniquePtr()
//	{
//		if (_ptr)
//		{
//			delete _ptr;
//			_ptr = nullptr;
//		}
//	}
//
//private:
//	T* _ptr;
//};

//void test()
//{
//	//unique_ptr：在没有赋值和拷贝的场景下，可以正常使用
//	//unique_ptr：防拷贝
//	unique_ptr<Date> up(new Date);
//	////拷贝构造是删除函数
//	//unique_ptr<Date> up2(up);
//	unique_ptr<Date> up3(new Date);
//	////赋值运算符是删除函数
//	//up3 = up;
//}















//template <class T>
//class AutoPtr
//{
//public:
//	AutoPtr(T* ptr)
//		:_ptr(ptr)
//	{}
//
//	AutoPtr(AutoPtr<T>& ap)
//		:_ptr(ap._ptr)
//	{
//		ap._ptr = nullptr;
//	}
//
//	AutoPtr<T>& operator=(AutoPtr<T>& ap)
//	{
//		if (this != &ap)
//		{
//			if (_ptr)
//				delete _ptr;
//			_ptr = ap._ptr;
//			ap._ptr = nullptr;
//		}
//	}
//
//	~AutoPtr()
//	{
//		if (_ptr)
//		{
//			delete _ptr;
//			_ptr = nullptr;
//		}
//	}
//private:
//	T* _ptr;
//};

//void test()
//{
//	AutoPtr<Date> ap(new Date);
//	AutoPtr<Date> ap2(ap);
//	AutoPtr<Date> ap3(new Date);
//	ap3 = ap2;
//
//}



//////////////auto_ptr有管理权转移的问题，不要使用此智能指针
//void test()
//{
//	auto_ptr<int> ap(new int(10));
//	*ap = 20;
//
//	auto_ptr<Date> ap2(new Date);
//	ap2->_y = 2021;
//	ap2->_m = 3;
//	ap2->_d = 20;
//
//	//智能指针拷贝，赋值问题：管理权转移
//	auto_ptr<Date> ap3 = ap2;
//}



//智能指针
//1.实现RAII思想
//2.实现指针的功能
//template <class T>
//class smartPtr
//{
//public:
//	//通过对象的生命周期管理资源的生命周期
//	smartPtr(T* ptr)
//		:_ptr(ptr)
//	{}
//	~smartPtr()
//	{
//		if (_ptr)
//		{
//			delete _ptr;
//			_ptr = nullptr;
//		}
//		cout << "~smartPtr()" << endl;
//	}
//	T& operator*()
//	{
//		return *_ptr;
//	}
//	T& operator->()
//	{
//		return _ptr;
//	}
//private:
//	T* _ptr;
//};
//
//void fun()
//{
//	smartPtr<int> sp(new int);
//	throw 10;
//}
//
//void test()
//{
//	try{
//		fun();
//	}
//	catch (int a)
//	{
//	}
//	cout << "test" << endl;
//}

//int main()
//{
//	test();
//	system("pause");
//	return 0;
//}