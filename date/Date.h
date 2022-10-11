#pragma once
#include <iostream>
using namespace std;
//using std::cout;
//using std::endl;

class Date {

	//友元函数
	friend ostream& operator<<(ostream& out, const Date& d);
	friend istream& operator>>(istream& in, Date& d);

private:
	int _year;
	int _month;
	int _day;

public:

	void Print() const; 

	Date(int year = 1900, int month = 1, int day = 1);

	Date(const Date& d);

	int GetMonthDay(int year, int month) const;


	// 赋值运算符重载
	// d2 = d3 -> d2.operator=(&d2, d3)
	Date& operator=(const Date& d) ;

	// 析构函数


	// 日期+=天数
	Date& operator+=(int day);

	// 日期+天数
	Date operator+(int day) const;

	// 日期-天数
	Date operator-(int day) const;

	// 日期-=天数
	Date& operator-=(int day);

	// 前置++
	Date& operator++();

	// 后置++
	Date operator++(int);

	// 后置--
	Date operator--(int);

	// 前置--
	Date& operator--();

	// >运算符重载
	bool operator>(const Date& d) const;

	// ==运算符重载
	bool operator==(const Date& d) const;

	// >=运算符重载
	inline bool operator >= (const Date& d) const;

	// <运算符重载
	bool operator < (const Date& d) const;

	// <=运算符重载
	bool operator <= (const Date& d) const;

	// !=运算符重载
	bool operator != (const Date& d) const;

	// 日期-日期 返回天数
	int operator-(const Date& d) const;

	//打印星期几
	void PrintWeekDay() const;

};

ostream& operator<<(ostream& out ,const Date& d);

istream& operator>>(istream& in, Date& d);

