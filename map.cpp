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
//	//���ݵ�Ԫ��pair����
//	pair<int, int> arr[] = { { 1, 2 }, { 3, 4 } };
//	map<int, int> mp3(arr, arr + 2);     //Ĭ�ϴ�С����
//	//map<int, int, greater<int>> mp3(arr, arr + 2);//�Ӵ�С
//	pair<string, int> arr2[] = { { "a", 10 }, { "bcd", 5 } };
//	map<string, int> mp4(arr2, arr2 + 2);
//
//	//��������key��С��ϵ������������������������
//	map<int, int>::iterator it = mp3.begin();
//	while (it != mp3.end())
//	{
//		//cout << *it << " ";   ����д��
//		//pair�ж����Ա������ͨ���������ļ�ͷ��������ÿ����Ա
//		cout << it->first << "--->" << it->second << endl;
//		//����ͨ���������޸�value�������޸�key
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
//	cout << "�޸ģ�" << endl;
//	//operator[]�޸Ĳ���
//	cout << mp4["a"] << endl;//10
//	mp4["a"] = 1000;
//	cout << mp4["a"] << endl;//1000
//
//	cout << "���룺" << endl;
//	//operator[]֧�ֲ������
//	mp4["f"] = 10;
//	printMap(mp4);
//
//	cout << "insert��" << endl;
//	//����pair���͵�����
//	//1.���ù��캯��   
//	//2.����make_pair����
//	mp4.insert(pair<string, int>("ffff", 5));
//	mp4.insert(make_pair("aaa", 6));
//	printMap(mp4);
//
//	//operator[]����K,V
//	//����ɹ�����pair���ݵĵ�����   ��ȡpair���ݵ�second(valueĬ��ֵ)
//	//ʧ�ܷ����Ѿ����ڵ�K��Ӧ�ĵ�����    ��ȡpair���ݵ�second(�Ѿ����ڵ�valueֵ)
//
//	//at:key�����ڣ����쳣
//	mp4.at("q");
//}
//
//int main()
//{
//	test();
//	system("pause");
//	return 0;
//}