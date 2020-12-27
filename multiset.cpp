//#include<iostream>
//#include<set>
//#include<functional>
//using namespace std;
//
//void test()
//{
//	multiset<int> s;
//	s.insert(1);
//	s.insert(5);
//	s.insert(1);
//	s.insert(1);
//	s.insert(9);
//	for (const auto& e : s)
//	{
//		cout << e << " ";
//	}
//	cout << endl;
//
//	pair<multiset<int>::iterator, multiset<int>::iterator> it = s.equal_range(1);
//	multiset<int>::iterator start = it.first;
//	while (start != it.second)
//	{
//		cout << *start << " ";
//		++start;
//	}
//	cout << endl;
//
//	//find返回第一个数据的位置
//	start = s.find(1);
//	cout << *start << endl;  //1
//
//	cout << s.count(1) << endl;  //3
//}
//
//int main()
//{
//	test();
//	system("pause");
//	return 0;
//}