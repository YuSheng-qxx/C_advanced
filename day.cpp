//#include<iostream>
//#include<string>
//using namespace std;
//#define SQR(A) A*A

//class Base
//{
//public:
//	Base(int j) :i(j){}
//	virtual ~Base(){}
//	void func1()
//	{
//		i *= 10;
//		func2();
//	}
//	int getValue()
//	{
//		return i;
//	}
//protected:
//	virtual void func2()
//	{
//		i++;
//	}
//	int i;
//};
//
//class Child :public Base
//{
//public:
//	Child(int j) :Base(j){}
//	void func1()
//	{
//		i *= 100;
//		func2();
//	}
//protected:
//	void func2()
//	{
//		i += 2;
//	}
//};
//int Fun(unsigned int n)
//{
//	n = (n & 0x55555555) + ((n >> 1) & 0x55555555);
//	n = (n & 0x33333333) + ((n >> 2) & 0x33333333);
//	n = (n & 0x0f0f0f0f) + ((n >> 4) & 0x0f0f0f0f);
//	n = (n & 0x00ff00ff) + ((n >> 8) & 0x00ff00ff);
//	n = (n & 0x0000ffff) + ((n >> 16) & 0x0000ffff);
//	return n;
//}
//int Find(char * pch)
//{
//	int count = 0;
//	char *p1 = pch;
//	while (*p1 != '\0')
//	{
//		if (*p1 == p1[1] - 1)
//		{
//			p1++;
//			count++;
//		}
//		else
//			break;
//	}
//	int count2 = 0;
//	while (*p1!='\0')
//	{
//		if (*p1 == p1[1] + 1)
//		{
//			p1++;
//			count2--;
//		}
//		else
//			break;
//	}
//	if (count2 == 0)
//		return count;
//	return (0);
//}
//void Mod(char* ptext)
//{
//	char *p1 = ptext;
//	char *p2 = p1;
//	while (*p1 != '\0')
//	{
//		int count = Find(p1);
//		if (count > 0)
//		{
//			*p2++ = *p1;
//			sprintf_s(p2, "%i", count);
//			while (*p2 != '\0')
//			{
//				p2++;
//			}
//			p1 += count + count + 1;
//		}
//		else
//			*p2++ = *p1++;
//	}
//}
//static int a = 1;
//void fun1()
//{
//	a = 2;
//}
//void fun2()
//{
//	int a = 3;
//}
//void fun3()
//{
//	static int a = 4;
//}
//class A
//{
//public:
//	void f()
//	{
//		cout << "A" << endl;
//	}
//};
//class B :public A
//{
//public:
//	virtual void f()
//	{
//		cout << "B" << endl;
//	}
//};
//class Base
//{
//public:
//	virtual int foo(int x)
//	{
//		return x * 10;
//	}
//	int foo(char x[14])
//	{
//		return sizeof(x)+10;
//	}
//};
//class Der :public Base
//{
//	int foo(int x)
//	{
//		return x * 20;
//	}
//	virtual int foo(char x[10])
//	{
//		return sizeof(x)+20;
//	}
//};
//void print(char *s)
//{
//	if (*s)
//	{
//		print(++s);
//		printf("%c", *s);
//	}
//}
//void Swap(int *a, int *b)
//{
//
//}
//
//int main()
//{
//	const int a = 10;
//	int *p = (int*)(&a);
//	*p = 20;
//	cout << "a= " << a << ", *p= " << *p << endl;
	/*int i = 3;
	cout << ++i << " " << ++i << endl;*/
	/*char xtr[] = "geneius";
	print(xtr);*/
	/*Der stde;
	Base* pst = &stde;
	char x[10];
	printf("%d\n", pst->foo(100) + pst->foo(x));*/
	/*A *a = new B;
	a->f();
	delete a;*/
	/*cout << a << endl;
	fun1();
	cout << a << endl;
	fun2();
	cout << a << endl;
	fun3();
	cout << a << endl;*/

	/*char text[32] = "XYBCDCBABABA";
	Mod(text);
	printf(text);*/
	/*int num = 10907;
	int count = 0;
	while (num)
	{
		count++;
		num /= 10;
	}
	cout << count << endl;*/
	//cout << Fun(197) << endl;
	/*Base *pb = new Child(1);
	pb->func1();
	cout << pb->getValue() << endl;
	delete pb;*/
	/*cout << sizeof("wang\0miao") <<" "  <<strlen("wang\0miao") << endl;*/
	/*char str[] = "glad to test something";
	char *p = str;
	p++;
	int *p1 = reinterpret_cast<int*>(p);
	p1++;
	p = reinterpret_cast<char*>(p1);
	printf("%s\n", p);*/
//	system("pause");
//	return 0;
//}

//class A
//{
//public:
//	int Get() const
//	{
//		vv = 1;
//		return vv;
//	}
//private:
//	mutable int vv;
//};

//class Base
//{
//public:
//	int bar(char x)
//	{
//		return (int)(x);
//	}
//	virtual int bar(int x)
//	{
//		return (2 * x);
//	}
//};
//class Derived :public Base
//{
//public:
//	int bar(char x)
//	{
//		return (int)(-x);
//	}
//	int bar(int x)
//	{
//		return (x / 2);
//	}
//};
//void func(const int& v1, const int& v2)
//{
//	cout << v1 << " " << v2 << endl;
//}
//int main()
//{
//	Derived obj;
//	Base *pobj = &obj;
//	printf("%d,", pobj->bar((char)(100)));
//	printf("%d", pobj->bar(100));
//	/*int i = 0;
//	func(++i, i++);*/
//	
//	/*int x = 6, y = 3, z = 2;
//	x /= SQR(y + z) / SQR(y + z);
//	cout << x << endl;*/
//	system("pause");
//	return 0;
//}