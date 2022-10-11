#define _CRT_SECURE_NO_WARNINGS 1

#include <set>
#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <queue>
#include <functional>
#include <assert.h>
using namespace std;

#include "AVLTree.h"
#include "RBTree.h"
#include "MyMap.h"
#include "MySet.h"

void test_map4()
{
	multimap<string, string> dict;
	dict.insert(make_pair("sort", "ÅÅĞò"));
	dict.insert(make_pair("left", "×ó±ß"));
	dict.insert(make_pair("left", "Ê£Óà"));
	dict.insert(make_pair("left", "Ê£Óà"));

	cout << dict.count("left") << endl;
}

int main()
{
	//test_map4();

	//TestAVLTree();
	//test_RBTree();
	//fmy::test_myMap();

	//fmy::test_myMap();

	fmy::test_set();
	return 0;
}





//void set_test1()
//{
//	set<int> s;
//
//	s.insert(1);
//	s.insert(1);
//	s.insert(4);
//	s.insert(6);
//	s.insert(1);
//	s.insert(5);
//	s.insert(8);
//	s.insert(9);
//
//
//	set<int>::iterator lt = s.begin();
//	while (lt != s.end())
//	{
//		cout << *lt << " ";
//		lt++;
//	}
//	cout << endl;
//
//	//set<int>::iterator = s.find(5);
//	/*auto f = s.find(5);
//
//	cout << *f << endl;*/
//}
//
//
//void set_test2()
//{
//	multiset<int> s1;
//	s1.insert(1);
//	s1.insert(1);
//	s1.insert(4);
//	s1.insert(8);
//	s1.insert(3);
//	s1.insert(6);
//	s1.insert(1);
//	s1.insert(5);
//	s1.insert(8);
//	s1.insert(9);
//	s1.insert(8);
//
//	set<int> s2;
//	s2.insert(1);
//	s2.insert(1);
//	s2.insert(4);
//	s2.insert(8);
//	s2.insert(3);
//	s2.insert(6);
//	s2.insert(1);
//	s2.insert(5);
//	s2.insert(8);
//	s2.insert(9);
//	s2.insert(8);
//	 
//	/*auto e = s1.begin();
//	while (e != s1.end())
//	{
//		*e+=10;
//		e++;
//	}
//	cout << endl;*/
//
//
//	auto e1 = s2.begin();
//	while (e1 != s2.end())
//	{
//		*e1 += 10;
//		e1++;
//	}
//	cout << endl;
//}
//
//
//
//int main()
//{
//	set_test2();
//
//
//	return 0;
//}