#pragma once
#include <iostream>
using namespace std;
//using std::cout;
//using std::endl;

class Date {

	//��Ԫ����
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


	// ��ֵ���������
	// d2 = d3 -> d2.operator=(&d2, d3)
	Date& operator=(const Date& d) ;

	// ��������


	// ����+=����
	Date& operator+=(int day);

	// ����+����
	Date operator+(int day) const;

	// ����-����
	Date operator-(int day) const;

	// ����-=����
	Date& operator-=(int day);

	// ǰ��++
	Date& operator++();

	// ����++
	Date operator++(int);

	// ����--
	Date operator--(int);

	// ǰ��--
	Date& operator--();

	// >���������
	bool operator>(const Date& d) const;

	// ==���������
	bool operator==(const Date& d) const;

	// >=���������
	inline bool operator >= (const Date& d) const;

	// <���������
	bool operator < (const Date& d) const;

	// <=���������
	bool operator <= (const Date& d) const;

	// !=���������
	bool operator != (const Date& d) const;

	// ����-���� ��������
	int operator-(const Date& d) const;

	//��ӡ���ڼ�
	void PrintWeekDay() const;

};

ostream& operator<<(ostream& out ,const Date& d);

istream& operator>>(istream& in, Date& d);

