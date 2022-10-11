#pragma once
#include <vector>
#include <list>
#include <forward_list>


namespace fmy 
{
	template<class T ,class Container= deque<T>>
	class stack
	{
	public:
		bool empty() const
		{
			return _con.empty();
		}

		size_t size() const
		{
			return _con.size();
		}

		const T& front() const
		{
			return _con.front();
		}

		const T& top() const
		{
			return _con.back();
		}

		void push(const T& x)
		{
			_con.push_back(x);
		}

		void pop()
		{
			_con.pop_back();
		}
	private:
		Container _con;
	};


}
