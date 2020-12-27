//#include<iostream>
//#include<map>
//#include<string>
//#include<functional>
//using namespace std;
//
//template<class K, class V>
//void printMap(const map<K, V>& mp)
//{
//	for (const auto& p : mp)
//	{
//		cout << p.first << "---->" << p.second << endl;
//	}
//}
//
//void test()
//{
//	map<int, int> mp;
//	map<string, int> mp2;
//	//数据单元：pair类型
//	pair<int, int> arr[] = { { 1, 2 }, { 3, 4 } };
//	map<int, int> mp3(arr, arr + 2);     //默认从小到大
//	//map<int, int, greater<int>> mp3(arr, arr + 2);//从大到小
//	pair<string, int> arr2[] = { { "a", 10 }, { "bcd", 5 } };
//	map<string, int> mp4(arr2, arr2 + 2);
//
//	//遍历按照key大小关系有序遍历：搜索树的中序遍历
//	map<int, int>::iterator it = mp3.begin();
//	while (it != mp3.end())
//	{
//		//cout << *it << " ";   错误写法
//		//pair有多个成员，可以通过迭代器的箭头操作访问每个成员
//		cout << it->first << "--->" << it->second << endl;
//		//可以通过迭代器修改value，不能修改key
//		++it;
//	}
//
//	map<string, int>::iterator it2 = mp4.begin();
//	while (it2 != mp4.end())
//	{
//		cout << it2->first << "--->" << it2->second << endl;
//		++it2;
//	}
//
//	cout << "修改：" << endl;
//	//operator[]修改操作
//	cout << mp4["a"] << endl;//10
//	mp4["a"] = 1000;
//	cout << mp4["a"] << endl;//1000
//
//	cout << "插入：" << endl;
//	//operator[]支持插入操作
//	mp4["f"] = 10;
//	printMap(mp4);
//
//	cout << "insert：" << endl;
//	//插入pair类型的数据
//	//1.调用构造函数   
//	//2.调用make_pair函数
//	mp4.insert(pair<string, int>("ffff", 5));
//	mp4.insert(make_pair("aaa", 6));
//	printMap(mp4);
//
//	//operator[]插入K,V
//	//插入成功返回pair数据的迭代器   获取pair数据的second(value默认值)
//	//失败返回已经存在的K对应的迭代器    获取pair数据的second(已经存在的value值)
//
//	//at:key不存在，抛异常
//	mp4.at("q");
//}
//
//int main()
//{
//	test();
//	system("pause");
//	return 0;
//}