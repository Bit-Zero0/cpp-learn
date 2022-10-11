#pragma once

namespace fmy
{
	template <class Iterator , class Ref , class Ptr>
	class reverse_iterator
	{
		typedef reverse_iterator<Iterator ,Ref , Ptr> self ;
	public:
		reverse_iterator(Iterator lt)
			:_lt(lt)
		{}

		Ref operator*() 
		{
			Iterator prev = _lt;
			return *--prev;
		}

		Ptr operator->()
		{
			return &operator*();
		}

		self& operator++()
		{
			--_lt;
			return *this;
		}

		self& operator--()
		{
			++_lt;
			return *this;
		}

		bool operator!=(const self& rit) const
		{
			return _lt != rit._lt;
		}
	private:
		Iterator _lt;
	};
}
