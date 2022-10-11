#pragma once
#include "HashTable.h"

namespace fmy
{
	template<class K, class V, class hash = Hash<K>>
	class unordered_map
	{
		struct MapKeyOfT
		{
			const K& operator()(const pair<K ,V>& kv)
			{
				return kv.first;
			}
		};

	public:
		typedef typename LinkHash::HashTable<K, pair<K, V>, MapKeyOfT, hash>::iterator iterator;

		iterator begin()
		{
			return _ht.begin();
		}

		iterator end()
		{
			return _ht.end();
		}

		pair<iterator, bool> insert(const pair<K, V>& kv)
		{
			return _ht.Insert(kv);
		}

		V& operator[](const K& key)
		{
			auto ret = _ht.Insert(make_pair(key, V()));
			return ret.first->second;
		}


	private:
		LinkHash::HashTable<K, pair<K, V>, MapKeyOfT, hash> _ht;
	};

	void test_unordered_map()
	{
		unordered_map<string, string> dict;
		dict.insert(make_pair("sort", "ÅÅÐò"));
		dict.insert(make_pair("string", "×Ö·û´®"));
		dict.insert(make_pair("map", "µØÍ¼¡¢Ó³Éä"));
		dict["left"] = "×ó±ß";
		cout << dict["sort"] << endl;
		cout << dict["left"] << endl;
		dict["right"] = "ÓÒ±ß";

		unordered_map<string, string>::iterator it = dict.begin();
		while (it != dict.end())
		{
			cout << it->first << ":" << it->second << endl;
			++it;
		}
		cout << endl;

		unordered_map<string, string> copy(dict);
		for (auto& kv : copy)
		{
			cout << kv.first << ":" << kv.second << endl;
		}
		cout << endl;
	}
}
