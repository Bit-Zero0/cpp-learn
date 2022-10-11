#pragma once

namespace fmy
{
	template<class T>
	struct Less
	{
		bool operator()(const T& x, const T& y) const
		{
			return x < y;
		}
	};

	template<class T>
	struct Greater{
		bool operator()(const T& x , const T& y) const{
			return x > y;
		}
	};

	template<class T, class Container = vector<T>, class Compare = Less<T> >
	class priority_queue
	{
	private:
		void adjust_up(size_t child)
		{
			Compare com;
			size_t parent = (child - 1) / 2;

			while (child > 0)
			{
				if (com(_con[parent], _con[child]))
				{
					swap(_con[parent], _con[child]);
					child = parent;
					parent = (child - 1) / 2;
				}
				else
				{
					break;
				}
			}
		}


		void adjust_down(size_t parent)
		{
			Compare com;
			size_t child = parent * 2 + 1;
			while (child < _con.size())
			{
				if (child + 1 < _con, size() && com(_con[child] < _con[child + 1]))
				{
					++child;
				}

				if (com(_con[parent], _con[child]))
				{
					swap(_con[parent], _con[child]);
					parent = child;
					child = parent * 2 + 1;
				}
				else
				{
					break;
				}
			}
		}

	public:
		priority_queue()
		{}

		template <class InputIterator>
		priority_queue(InputIterator first, InputIterator last)
			:_con(first , last)
		{
			for (int i = (_con.size() - 1 - 1) / 2; i >= 0; --i)
			{
				abjust_down(i);
			}
		}

		void push(const T& x)
		{
			_con.push(x);
			adjust_up(_con.size() - 1);
		}

		void pop()
		{
			swap(_con[0], _con[size() - 1]);
			_con.pop();
			adjust_down(0);
		}

		const T& top()
		{
			return _con[0];
		}

		size_t size()
		{
			return _con.size();
		}

		bool empty()
		{
			return _con.empty();
		}

	private:
		Container _con;
	};

	
}
