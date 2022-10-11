#define _CRT_SECURE_NO_WARNINGS 1
#include "stack.h"
#include "queue.h"
#include "priority_queue.h"
#include <iostream>
#include <vector>
#include <list>
#include <functional>

#include <stack>
#include <queue>

using namespace std;

void test1()
{
	fmy::stack<int , std::vector<int>> s;

	s.push(10);
	s.push(20);
	s.push(30);
	s.push(40);

	while (!s.empty())
	{
		cout << s.top() << " ";
		s.pop();
	}
	cout << endl;

}

void test2()
{
	fmy::queue<int ,list<int>> q;
	q.push(1);
	q.push(2);
	q.push(3);
	q.push(4);

	while (!q.empty())
	{
		cout << q.front() << " ";
		q.pop();
	}
	cout << endl;
}



void test_priority_queue()
{
	priority_queue<int , vector<int> ,fmy::Less<int>> pq;
	pq.push(1);
	pq.push(2);
	pq.push(6);
	pq.push(4);
	pq.push(1);

	while (!pq.empty())
	{
		cout << pq.top() << " ";
		pq.pop();
		cout << endl;
	}
}

int main()
{
	//test2();

	test_priority_queue();
	return 0;
}