#pragma once
#include<vector>
#include<list>

namespace fmy
{
	// stack<int, vector<int>> s;
	// stack<int, list<int>> s;

	template<class T, class Container = deque<T>>
	class queue
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

		const T& back() const
		{
			return _con.back();
		}

		void push(const T& x)
		{
			_con.push_back(x);
		}

		void pop()
		{
			_con.pop_front();
		}
	private:
		Container _con;
	};
}
