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
		cout << "输入的是非法日期:";
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

		if (_month == 13)//当_moth == 13 时 ， 则说明过了一年。
		{
			_month = 1;
			++_year;
		}
	}
	return *this;
}


Date Date::operator+(int day) const
{
	Date ret(*this);//拷贝构造

	ret += day; //相当于 ret.operator+=(day);

	return ret;
}


Date& Date::operator-=(int day)
{
	if (day < 0)
	{
		return *this += -day;
	}
	_day -= day;
	
	while (_day <= 0)//如果 _day <= 0,则说明不在本月，也是之前的日子
	{
		--_month; //先减月份，因为已经进入while循环， _day -= day 则说明已经以及是上一个月的日子了，
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


//++d  前置++
Date& Date::operator++()
{
	*this += 1;

	return *this;
}

//d++  后置++
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
	const char* arr[] = { "星期一" , "星期二" ,"星期三","星期四" ,"星期五" , "星期六" ,"星期天" };
	int count = *this - Date(1900, 1, 1); //1900年1月1日 是世界上第一个 星期一。 *this - Date(1900, 1, 1) 得到至今到第一个星期一的天数。
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


