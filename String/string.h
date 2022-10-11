#pragma once
#include <string>
#include <assert.h>
#include <iostream>

using namespace std;
namespace fmy {

	class string {

	private:
		size_t _size;
		size_t _capacity;
		char* _str;

		static const size_t npos = -1;

	public:

		typedef char* iterator;
		typedef const char* const_iterator;

		iterator begin()
		{
			return _str;
		}
		
		iterator end()
		{
			return _str + _size;
		}

		const_iterator begin() const
		{
			return _str;
		}

		const_iterator end() const
		{
			return _str + _size;
		}

		string(const char* str = "") //当我们进行深拷贝时，如果没有目标 字符 ，则创建空字符串
			:_size(strlen(str)) //没有字符，则为 0 。
			,_capacity(_size) //_size为0 ，则 _capacity 也为0
		{
			_str = new char[_capacity + 1]; //开辟空间，+1是因为要给 '\0' 留一个位
			strcpy(_str, str); 
		}

		////拷贝构造  s1(s)   
		//string(const string& s)
		//	:_size(s._size)
		//	,_capacity(s._capacity)
		//{
		//	_str = new char[_capacity + 1];
		//	strcpy(_str, s._str);
		//}


		void swap(string& s)
		{
			std::swap(_size, s._size);
			std::swap(_capacity, s._capacity);
			std::swap(_str, s._str);
		}

		//拷贝构造的现代写法
		string(string& s)
			:_size(0)
			,_capacity(0)
			,_str(nullptr)
		{
			string tmp(s._str);
			swap(tmp);
		}

		~string()
		{
			delete[] _str;
			_str = nullptr;
			_size = _capacity = 0;
		}

		////此方法有缺陷，不能自己给自己赋值 如：  s3 = s3 , 因为他会把自己先给释放了，所以之后赋值的内容就是乱码了
		//string& operator=(const string& s)
		//{
		//	delete[] _str;
		//	_str = new char[strlen(s._str) + 1]; // new是有可能会开辟空间失败的，那时抛异常后就会返回，但是我们之前却把 _str 给释放了
		//	strcpy(_str, s._str);

		//	return *this;
		//}

		//string& operator=(const string& s)
		//{
		//	if (this != &s) //注意 this 和 &s 是取到的地址
		//	{
		//		char* tmp = new char[strlen(s._str) + 1]; //因为new有可能开辟失败，所以使用tmp来暂存
		//		strcpy(tmp, s._str);
		//		delete[] _str; //当new开辟失败时，也不会影响到 _str了
		//		_str = tmp;
		//		_size = s._size;
		//		_capacity = s._capacity;
		//	}
		//	return *this;
		//}

		string& operator=(string s)
		{
			swap(s);
			return *this;
		}



		const char* c_str() const  //将string转化为C语言中字符串
		{
			return _str;
		}

		size_t size() const
		{
			return _size;
		}

		const char& operator[](size_t pos) const //const 修饰放回值，可以避免返回值被修改，但是同样的，也需要const修饰对象才能调用。
		{
			assert(pos < _size); //使用assert防止数组越界，如果越界，assert就会直接终止程序，并报错 
			return _str[pos];
		}

		char& operator[](size_t pos)
		{
			assert(pos < _size);
			return _str[pos];
		}

		void push_back(char ch)
		{
			if (_size == _capacity)
			{
				reserve(_capacity == 0 ? 4 : _capacity * 2);
			}
			_str[_size] = ch;
			++_size;
			_str[_size] = '\0';

			//insert(_size , ch);
		}

		void reserve(size_t n)
		{
			if (n > _capacity)
			{
				char* tmp = new char[n + 1];
				strcpy(tmp, _str);
				delete[] _str;

				_str = tmp;

				_capacity = n;
			}
		}

		void resize(size_t n, char ch = '\0')
		{
			if (n <= _size)
			{
				_size = n;
				_str[_size];
			}
			else
			{
				if (n > _capacity)
				{
					reserve(n);
				}
				memset(_str + _size, ch, n - _size);
				_size = n;
				_str[_size] = '\0';
			}
		}

		string& insert(size_t pos, char ch)
		{
			assert(pos <= _size); //因为要有可能尾插，所以是 <= _size、

			if (_size == _capacity)
			{
				reserve(_capacity == 0 ? 4 : _capacity * 2);
			}

			size_t end = _size + 1;
			while (end > pos)
			{
				_str[end] = _str[end - 1];
				end--;
			}

			_str[pos] = ch;
			_size++;
			
			return *this;
		}

		string& insert(size_t pos, const char* s)
		{
			assert(pos <= _size);
			size_t len = strlen(s);
			if (_size + len > _capacity)
			{
				reserve(_size + len);
			}

			size_t end = _size + len;
			while (end >= pos+len) 
			{
				_str[end] = _str[end - len];
				--end;
			}
			
			strncpy(_str + pos, s, len);
			_size += len;
			return *this;
		}

		void append(const char* str)
		{
			/*size_t len = strlen(str);
			if (_size + len > _capacity)
			{
				reserve(_size + len);
			}
			strcpy(_str + _size, str);
			_size += len;*/

			insert(_size, str);
		}

		string& operator+=(const char* str)
		{
			append(str);
			return *this;
		}

		string& operator+=(char ch)
		{
			push_back(ch);
			return *this;
		}

		size_t find(char ch)
		{
			for (size_t i = 0; i < _size; ++i)
			{
				if (ch == _str[i])
				{
					return i;
				}
			}
			return npos;
		}


		size_t find(char* s, size_t pos = 0)
		{
			const char* ptr = strstr(_str + pos , s);
			if (ptr == nullptr)
			{
				return npos;
			}
			else
			{
				return ptr - _str; //指针减指针可以得到两个之间相隔的距离。
			}
		}

		string& erase(size_t pos = 0, size_t len = npos)
		{
			assert(pos < _size);

			if (len == npos || len + pos >= _size)
			{
				_str[pos] = '\0';
				_size = pos;
			}
			else
			{
				strcpy(_str + pos, _str + pos + len);
				_size -= len;
			}
			return *this;
		}
		
		void clear()
		{
			_str[0] = '\0';
			_size = 0;
		}
	};
	//const size_t string::npos = -1;

	bool operator<(const string& s1, const string& s2)
	{
		size_t l1 = 0, l2 = 0;
		while (l1 < s1.size() && l2 < s2.size())
		{
			if (s1[l1] < s2[l2])
				return true;
			else if (s1[l1] > s2[l2])
				return false;
			else
			{
				l1++;
				l2++;
			}
		}
		return l2 < s2.size() ? true : false;

		//strcmp(s1.c_str() , s2.c_str());
	}

	bool operator==(string& s1, string& s2)
	{
		return strcmp(s1.c_str(), s2.c_str()) == 0;
	}

	bool operator>=(string& s1, string& s2)
	{
		return !(s1 < s2) ;
	}

	bool operator>(string& s1, string& s2)
	{
		return !(s1 >= s2);
	}

	bool operator<=(string& s1, string& s2)
	{
		return !(s1 > s2);
	}

	bool operator!=(string& s1, string& s2)
	{
		return !(s1 == s2);
	}

	ostream& operator<<(ostream& out, const string& s)
	{
		for (auto ch : s)
		{
			out << ch;
		}
		return out;
	}

	istream& operator>>(istream& in, string& s)
	{
		s.clear();

		char ch = in.get();

		while (ch != '\n' && ch != ' ')
		{
			s += ch;
			ch = in.get();
		}

		return in;
	}
}