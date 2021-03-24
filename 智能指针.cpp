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



//shared_ptr��
//֧�ֿ����͸�ֵ
//ͨ�����ü�����֤��Դ����ȷ��Ψһ���ͷ�
//���߳��У�ͨ�������ý��д��в�������֤����������ȷ
//ÿ����Դ�����Լ����������ü���
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
//		//�жϹ������Դ�Ƿ�Ϊͬһ����Դ
//		if (_ptr != sp._ptr)
//		{
//			//������--
//			//���������Ϊ0����ǰ���������һ��������Դ�Ķ���
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
//			//�������ۼ�
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
//	//ÿһ����Դ��һ����������
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
//	//unique_ptr����û�и�ֵ�Ϳ����ĳ����£���������ʹ��
//	//unique_ptr��������
//	unique_ptr<Date> up(new Date);
//	////����������ɾ������
//	//unique_ptr<Date> up2(up);
//	unique_ptr<Date> up3(new Date);
//	////��ֵ�������ɾ������
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



//////////////auto_ptr�й���Ȩת�Ƶ����⣬��Ҫʹ�ô�����ָ��
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
//	//����ָ�뿽������ֵ���⣺����Ȩת��
//	auto_ptr<Date> ap3 = ap2;
//}



//����ָ��
//1.ʵ��RAII˼��
//2.ʵ��ָ��Ĺ���
//template <class T>
//class smartPtr
//{
//public:
//	//ͨ��������������ڹ�����Դ����������
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