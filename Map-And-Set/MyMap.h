#pragma once
#include "RBTree.h"


namespace fmy
{
	template<class K, class V>
	class map
	{
	public:
		struct MapKeyOfT
		{
			const K& operator()(const pair<K, V>& kv)
			{
				return kv.first;
			}
		};


		typedef typename RBTree<K, pair<K, V>, MapKeyOfT>::iterator iterator;


		iterator begin()
		{
			return _t.begin();
		}

		iterator end()
		{
			return _t.end();
		}

		pair<iterator,bool> insert(const pair<K,V>& kv)
		{
			return _t.Insert(kv);
		}

		iterator find()
		{
			_t.Find();
		}

		V& operator[] (const K& key)
		{
			auto ret = _t.Insert(make_pair(key, V()));
			return ret.first->second;
		}

	private:
		RBTree<K, pair<K, V>, MapKeyOfT > _t;
	};



	void test_myMap()
	{
		map<string, string> dict;
		dict.insert(make_pair("sort", " "));
		dict.insert(make_pair("string","ַjhk"));
		dict.insert(make_pair("map", "sd"));

		dict["left"];
		dict["left"] = "酘晚";
		dict["map"] = "華芞﹜茬扞";

		auto it = dict.begin();
		while (it != dict.end())
		{
			cout << it->first << ":" << it->second << endl;
			++it;
		}
		cout << endl;
	}
}
