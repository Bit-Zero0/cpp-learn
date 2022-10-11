#define _CRT_SECURE_NO_WARNINGS 1
#include "Date.h"


Date::Date(int year , int month , int day)
{
	_year = year;
	_month = month;
	_day = day;

	if (!(year > 0
		&& (month > 0 && month < 13)
		&& (day > 0 && day <= GetMonthDay(year, month))))
	{
		cout << "������ǷǷ�����:";
		Print();
	}
}

Date::Date(const Date& d)
{
	_year = d._year  ;
	_month = d._month;
	_day = d._day;
}

int Date::GetMonthDay(int year, int month) const
{
	int MonthDay[12] = { 31 ,28, 31, 30,31,30,31,31,30,31,30,31 };
	int day = MonthDay[month - 1];
	if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)))
	{
		day += 1;
	}
	return day;
}

void Date::Print() const
{
	cout << _year << "-" << _month << "-" << _day << endl;
}


Date& Date::operator=(const Date& d)
{
	_year = d._year;
	_month = d._month;
	_day = d._day;

	return *this;
}

Date& Date::operator+=(int day)
{
	if (day < 0)
	{
		return *this -= day;
	}

	_day += day;
	while (_day > GetMonthDay(_year, _month))
	{
		_day -= GetMonthDay(_year, _month);
		++_month;

		if (_month == 13)//��_moth == 13 ʱ �� ��˵������һ�ꡣ
		{
			_month = 1;
			++_year;
		}
	}
	return *this;
}


Date Date::operator+(int day) const
{
	Date ret(*this);//��������

	ret += day; //�൱�� ret.operator+=(day);

	return ret;
}


Date& Date::operator-=(int day)
{
	if (day < 0)
	{
		return *this += -day;
	}
	_day -= day;
	
	while (_day <= 0)//��� _day <= 0,��˵�����ڱ��£�Ҳ��֮ǰ������
	{
		--_month; //�ȼ��·ݣ���Ϊ�Ѿ�����whileѭ���� _day -= day ��˵���Ѿ��Լ�����һ���µ������ˣ�
		if (_month == 0)
		{
			--_year;
			_month = 12;
		}
		_day += GetMonthDay(_year, _month);
	}
	return *this;
}

Date Date::operator-(int day) const
{
	Date ret(*this);

	ret -= day;

	return ret;
}


//++d  ǰ��++
Date& Date::operator++()
{
	*this += 1;

	return *this;
}

//d++  ����++
Date Date:: operator++(int)
{
	Date ret(*this);

	*this += 1;

	return ret;
}

//--d
Date& Date::operator--()
{
	*this -= 1;

	return *this;
}

//d--
Date Date::operator--(int)
{
	Date ret(*this);

	*this -= 1;

	return ret;
}

bool Date::operator==(const Date& d) const
{
	return _year == d._year
		&& _month == d._month
		&& _day == d._day;
}


bool Date::operator>(const Date& d) const
{
	if (_year > d._year)
	{
		return true;
	}
	else if (_year == d._year && _month > d._month)
	{
		return true;
	}
	else if (_year == d._year && _month == d._month && _day > d._day)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Date::operator>=(const Date& d) const
{
	return *this > d || *this == d;
}

bool Date::operator<(const Date& d) const
{
	return !(*this >= d);
}

bool Date::operator<=(const Date& d)const
{
	return !(*this > d);
}

bool Date::operator!=(const Date& d) const
{
	return !(*this == d);
}


int Date::operator-(const Date& d)const
{
	Date max = *this;
	Date min = d;
	int flag = 1;

	if (*this < d)
	{
		max = d;
		min = *this;
		flag = -1;
	}

	int count = 0;
	while (min != max)
	{
		++min;
		++count;
	}

	return count * flag;
}

void Date::PrintWeekDay() const
{
	const char* arr[] = { "����һ" , "���ڶ�" ,"������","������" ,"������" , "������" ,"������" };
	int count = *this - Date(1900, 1, 1); //1900��1��1�� �������ϵ�һ�� ����һ�� *this - Date(1900, 1, 1) �õ����񵽵�һ������һ��������
	cout << arr[count % 7] << endl;
}


ostream& operator<<(ostream& out,const Date& d)
{
	return out << d._year << "/" << d._month << "/" << d._day << endl;
}

istream& operator>>(istream& in, Date& d)
{
	return in >> d._year >> d._month >> d._day;
}


