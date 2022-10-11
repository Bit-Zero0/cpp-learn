#pragma once
#include "HashTable.h"

namespace fmy
{
	template<class K , class hash = Hash<K>>
	class unordered_set
	{
		struct SetKeyOfT
		{
			const K& operator()(const K& key)
			{
				return key;
			}
		};

	public:
		typedef typename LinkHash::HashTable<K, K, SetKeyOfT, hash>::iterator iterator;

		iterator begin()
		{
			return _ht.begin();
		}

		iterator end()
		{
			return _ht.end();
		}

		pair<iterator, bool> insert(const K& key)
		{
			return _ht.Insert(key);
		}



	private:
		LinkHash::HashTable<K, K, SetKeyOfT, hash> _ht;
	};

	void test_unordered_set()
	{

		/*unordered_set<int> us;
		us.insert(4);
		us.insert(14);
		us.insert(34);
		us.insert(7);
		us.insert(24);
		us.insert(17);
		unordered_set<int>::iterator it = us.begin();
		while (it != us.end())
		{
			cout << *it << " ";
			++it;
		}
		cout<<endl;

		unordered_set<string> uss;
		uss.insert("sort");
		uss.insert("hash");

		unordered_set<string>::iterator itt = uss.begin();
		while (itt != uss.end())
		{
			cout << *itt << " ";
			++itt;
		}*/

		unordered_set<int> us;
		for (size_t i = 0; i < 100; ++i)
		{
			us.insert(i);
		}
	}
}
