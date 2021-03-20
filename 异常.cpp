//#include<iostream>
//#include<atomic>
//using namespace std;
//
//void fun()
//{
//	try
//	{
//		//监控异常
//		throw 10;
//	}
//	catch (int a)//捕捉对应类型的异常
//	{
//		cout << a << endl;
//		cout << "catch int" << endl;
//	}
//	catch (...)
//	{
//		cout << "catch ..." << endl;
//	}
//	cout << "继续执行" << endl;
//}
//
//void test()
//{
//	try
//	{
//		//监控异常
//		fun();
//	}
//	catch (int a)//捕捉对应类型的异常
//	{
//		cout << "test catch int" << endl;
//	}
//	catch (...)
//	{
//		cout << "test catch ..." << endl;
//	}
//	cout << "test 继续执行" << endl;
//}
//
//int main()
//{
//	test();
//	system("pause");
//	return 0;
//}