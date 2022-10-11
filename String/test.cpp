#define _CRT_SECURE_NO_WARNINGS 1

#include "string.h"
using namespace fmy;
using std::cout;
using std::cin;


void f(const fmy::string& s) //这里的 s 使用了const修饰，所以它会调用带有 operator[] 中this指针带有 const修饰的函数  
{
	cout << s[0] << endl;
}

void test1()
{
	fmy::string s1 ="emm";
	cout << s1.size() << endl;

	fmy::string s2(s1);
	cout << s2.size() << endl;

	fmy::string s3 = s2;
	cout << s3.size() << endl;

	cout << s1[0] << endl;
	cout << s2[1] << endl;
	cout << s3[2] << endl;

	f(s1);

}

void test2()
{
	fmy::string s = "hello world";
	fmy::string::iterator i = s.begin();
	/*while (i != s.end())
	{
		*i += 1;
		i++;
	}

	i = s.begin();
	while (i != s.end())
	{
		cout << *i << ' ';
		i++;
	}*/

	for (auto j : s)
	{
		cout << j << ' ';
	}
}


void test3()
{
	fmy::string s = "hello";

	s.append("123");

	for (int i = 0; i < s.size(); i++)
	{
		cout << s[i];
	}
	cout << endl;

	s.insert(5, " emm");
	for (int i = 0; i < s.size(); i++)
	{
		cout << s[i];
	}
	cout << endl;

	s += 'a';
	cout << s.c_str() << endl;

	s += "bc";
	cout << s.c_str() << endl;

	s += " def";
	cout << s.c_str() << endl;


	s.erase(10);
	cout << s.c_str() << endl;
	
	s.erase(6 , 2);
	cout << s.c_str() << endl;

	s.erase(0,2);
	cout << s.c_str() << endl;

	s.erase(0, 3);
	cout << s.c_str() << endl;
}


void test4()
{
	fmy::string s = "abc";

	fmy::string s1 ;

	s1 = s;

	cout << s1.c_str() << endl;
}
void test5()
{
	fmy::string s("emm123");



	cout << s.c_str() << endl;

	fmy::string s1("emm");
	cout << (s >= s1) << endl;

	fmy::string s2(s1);
	s2.erase(1, 1);
	cout << (s2 >= s1) << endl;

	fmy::string s3(s1);
	cout << (s3 >= s1) << endl;


}


void test6()
{
	fmy::string s1("hello");
	cout << s1<< endl;;

	fmy::string s2;
	cin >> s2;
	cout << s2 << endl;

	cin >> s2;
	cout << s2 << endl;

	s2.insert(5, '1');

}


int main()
{
	test6();


	
	return 0;
}