//#include<iostream>
//#include<atomic>
//using namespace std;
//
//void fun()
//{
//	try
//	{
//		//����쳣
//		throw 10;
//	}
//	catch (int a)//��׽��Ӧ���͵��쳣
//	{
//		cout << a << endl;
//		cout << "catch int" << endl;
//	}
//	catch (...)
//	{
//		cout << "catch ..." << endl;
//	}
//	cout << "����ִ��" << endl;
//}
//
//void test()
//{
//	try
//	{
//		//����쳣
//		fun();
//	}
//	catch (int a)//��׽��Ӧ���͵��쳣
//	{
//		cout << "test catch int" << endl;
//	}
//	catch (...)
//	{
//		cout << "test catch ..." << endl;
//	}
//	cout << "test ����ִ��" << endl;
//}
//
//int main()
//{
//	test();
//	system("pause");
//	return 0;
//}