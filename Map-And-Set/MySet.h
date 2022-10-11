#pragma once
#include "RBTree.h"

namespace fmy 
{
	template<class K>
	class set
	{
	public:
		struct SetKeyOfT
		{
			const K& operator()(const K& key)
			{
				return key;
			}
		};

		typedef typename RBTree<K, K, SetKeyOfT>::iterator iterator;

		iterator begin()
		{
			return _t.begin();
		}

		iterator end()
		{
			return _t.end();
		}

		pair<iterator , bool> insert(const K& key)
		{
			return _t.Insert(key);
		}

		iterator find(const K& key)
		{
			return _t.Find(key);
		}
	private:
		RBTree<K, K ,SetKeyOfT> _t;
	};

	void test_set()
	{
		set<int> s;
		s.insert(1);
		s.insert(4);
		s.insert(2);
		s.insert(24);
		s.insert(2);
		s.insert(12);
		s.insert(6);

		set<int>::iterator it = s.begin();
		while (it != s.end())
		{
			cout << *it << " ";
			++it;
		}
		cout << endl;

		for (auto e : s)
		{
			cout << e << " ";
		}
		cout << endl;

		set<int> copy(s);
		for (auto e : copy)
		{
			cout << e << " ";
		}
		cout << endl;

		set<int> ss;
		ss.insert(111);
		ss.insert(422);

		copy = ss;
		for (auto e : copy)
		{
			cout << e << " ";
		}
		cout << endl;
	}
}


