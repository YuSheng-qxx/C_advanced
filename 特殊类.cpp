#include<iostream>
#include<memory>
#include<mutex>
#include<thread>
using namespace std;

//����ģʽ---���߳�
class Singleton
{
public:
	//static���з�����������:��һ�ε���ʱ��������
	static Singleton* getOBJ()
	{
		//���Ч��
		if (_ptr == nullptr)
		{
			_mtx.lock();
			//��������:��һ�ε���ʱ��������
			//��֤����
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
	//���캯��˽��
	Singleton()
	{
		cout << "Singleton()" << endl;
	}

	//������
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



////����ģʽ---���߳�
//class Singleton
//{
//public:
//	//static���з�����������:��һ�ε���ʱ��������
//	static Singleton* getOBJ()
//	{
//		//��������:��һ��ʹ��ʱ����
//		if (_ptr == nullptr)
//		{
//			_ptr = new Singleton;
//		}
//		return _ptr;
//	}
//private:
//	//���캯��˽��
//	Singleton()
//	{
//		cout << "Singleton()" << endl;
//	}
//
//	//������
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





////����ģʽ
//class Singleton
//{
//public:
//	//���е�static����
//	static Singleton& getOBJ()
//	{
//		return _singleton;
//	}
//private:
//	//���캯��˽�л�
//	Singleton()
//	{}
//
//	//������
//	Singleton(const Singleton&) = delete;
//
//	//static��Ա
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


















//ֻ����ջ�ϴ�������
//class StackOnly
//{
//	//�ض���operator
//	void* operator new(size_t n) = delete;
//	void operator delete(void* ptr) = delete;
//};
//
//void test()
//{
//	StackOnly so;
//	//StackOnly* ptr = new StackOnly;
//}



//ֻ����ջ�ϴ�������
//class StackOnly
//{
//public:
//	//���еķ���,��ջ�ϴ�������
//	static StackOnly getOBJ()
//	{
//		StackOnly so;
//		return so;
//	}
//
//private:
//	//���캯��˽�л�
//	StackOnly()
//	{}
//};
//
//void test()
//{
//	//StackOnly* p = new StackOnly;
//	StackOnly so = StackOnly::getOBJ();
//}












//ֻ���ڶ��ϴ�������
//class HeapOnly
//{
//public:
//	//���еķ�������������
//	static HeapOnly* getOBJ()
//	{
//		//���ϴ�������
//		return new HeapOnly;
//	}
//private:
//	//���캯��˽�л�
//	HeapOnly()
//	{}
//
//	//������
//	//��������˽�л�
//	HeapOnly(const HeapOnly& ho);
//	//����ֱ�Ӷ����delete����
//	HeapOnly(const HeapOnly& ho) = delete;
//};
//
//void test()
//{
//	//ջ�ϵĶ���
//	//HeapOnly ho;
//
//	//���ϵĶ���
//	HeapOnly* ptr1 = HeapOnly::getOBJ();
//	HeapOnly* ptr2 = HeapOnly::getOBJ();
//
//	//ջ�ϵĶ���
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