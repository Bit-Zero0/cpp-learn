#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include "list.h"
#include <List>
#include "vector.h"

using namespace fmy;
using std::cout;
using std::endl;


void test1()
{
list<int> lt;
lt.push_back(1);
lt.push_back(2);
lt.push_back(3);
lt.push_back(4);

//lt.f();

// 访问修改容器
list<int>::iterator it = lt.begin();
while (it != lt.end())
{
	*it *= 2; // 修改
	cout << *it << " ";
	++it;
}
cout << endl;

print_list(lt);
}

void test2()
{
	std::list<int> lt;
	lt.push_back(1);
	lt.push_back(3);
	lt.push_back(3);
	lt.push_back(3);
	lt.push_back(2);
	lt.push_back(4);
	lt.push_back(3);

	for (auto e : lt)
	{
		cout << e << " ";
	}
	cout << endl;

	lt.sort();

	for (auto e : lt)
	{
		cout << e << " ";
	}
	cout << endl;

	lt.reverse();
	for (auto e : lt)
	{
		cout << e << " ";
	}
	cout << endl;

	lt.unique();
	for (auto e : lt)
	{
		cout << e << " ";
	}
	cout << endl;

}

void test3()
{
	list<int> lt1(2, 99);
	print_list(lt1);

	list<int> lt2(lt1);
	print_list(lt2);

	list<int> lt3;
	lt3 = lt2;
	print_list(lt3);

	lt3.push_back(44);
	lt3.push_back(66);
	lt3.push_back(68);
	lt3.push_back(87);

	print_list(lt3);

	list<int>::iterator b = lt3.begin();
	while (b != lt3.end())
	{
		if (b._node->_data == 66)
		{
			b = lt3.erase(b); //必须要考虑到迭代器失效，所以必须为b = erase 的返回值。 
		}
		else
		{
			++b;
		}
	}                               
	print_list(lt3);

	list<int>::iterator c = lt3.begin();
	while (c != lt3.end())
	{
		if (c._node->_data == 68)
		{
			lt3.insert(c, 77);
			++c;
		}
		else
		{
			++c;
		}
	}
	print_list(lt3);

	//lt3.pop_back();
	//lt3.pop_back();
	//print_list(lt3);

	//lt3.pop_front();
	//lt3.pop_front();
	//print_list(lt3);
}

void test4()
{
	list<int> lt;
	lt.push_back(11);
	lt.push_back(22);
	lt.push_back(33);
	lt.push_back(44);
	lt.push_back(55);
	lt.push_back(66);
	lt.push_back(77);
	lt.push_back(88);
	lt.push_back(99);

	list<int>::iterator emm = lt.begin();
	while (emm != lt.end())
	{
		cout << *emm << " ";
		++emm;
	}
	cout << endl;

	list<int>::reverse_iterator b = lt.rbegin();
	while (b != lt.rend())
	{
		cout << *b << " ";
		++b;
	}
	cout << endl;

}


void test5()
{
	vector<int> v1;
	v1.push_back(1);
	v1.push_back(2);
	v1.push_back(3);
	v1.push_back(4);
	v1.push_back(5);

	vector<int>::reverse_iterator it = v1.rbegin();
	while (it != v1.rend())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;

}

int main()
{
	test3();
	return 0;
}