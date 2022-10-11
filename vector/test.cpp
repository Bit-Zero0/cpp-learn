#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <algorithm>

using namespace std;
#include "vector.h"
using fmy::vector;

void test1()
{
	vector<int> v;

	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	v.push_back(5);

	for (size_t i = 0; i < v.size(); i++)
	{
		std::cout << v[i] << std::endl;
	}
}


void test2()
{
	vector<char> v;
	v.reserve(10);
	v.push_back('a');
	v.push_back('b');
	v.push_back('c');
	v.push_back('d');

	v.resize(16, 'A');

	for (size_t i = 0; i < v.size(); i++)
	{
		std::cout << v[i] << std::endl;
	}


}


void test3()
{
	vector<int> v;
	v.push_back(6);
	v.push_back(66);

	vector<int> v1(v);

}

void test4()
{

	vector<int> v;

	v.insert(v.begin(), 666);
	v.push_back(6);
	vector<int>::iterator ret = find(v.begin() , v.end() , 6);
	if (ret != v.end())
	{
		cout << "找到了" << endl;
		v.insert(ret,66);
	}

	v.print();


	ret = find(v.begin(), v.end(), 6);
	if (ret != v.end())
	{
		cout << "准备删除" << endl;
		v.erase(ret);
	}

	v.print();

	v.erase(v.begin());
	v.print();

}


void test5()
{
	vector<int> v;
	v.push_back(1);
	v.push_back(2);
	//v.push_back(3);
	v.push_back(4);
	v.push_back(5);
	//v.push_back(6);
	
	//删除v中所有的偶数
	vector<int>::iterator ret = v.begin();
	while (ret != v.end())
	{
		if (*ret % 2 == 0)
		{
			v.erase(ret);
		}
		else
		{
		++ret;
		}
	}

	v.print();
}


int main()
{
	test5();

	return 0;
}