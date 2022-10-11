#pragma once
#include <vector>
#include <string>

template<class K>
struct Hash
{
	size_t operator()(const K& key)
	{
		return key;
	}
};

template<>
struct Hash <string>
{
	size_t operator()(const string& s)
	{
		//BKDR哈希
		size_t  value = 0;
		for (auto ch : s)
		{
			value *= 31;
			value += ch;
		}
		return value;
	}
};

namespace LinkHash
{
	template<class T>
	struct HashNode
	{
		T _data; 
		HashNode<T>* _next;

		HashNode(const T& data)
			: _data(data)
			, _next(nullptr)
		{}
	};

	//声明HashTable，使得__HTIterator能够识别
	template<class K, class T, class KeyOfT, class HashFunc>
	class HashTable;

	template<class K, class T, class Ref, class Ptr, class KeyOfT, class HashFunc>
	struct __HTIterator
	{
		typedef HashNode<T> Node;
		typedef __HTIterator< K, T, Ref, Ptr, KeyOfT, HashFunc> Self;

		Node* _node;
		HashTable<K, T, KeyOfT, HashFunc>* _pht;

		__HTIterator(Node* node , HashTable<K, T, KeyOfT, HashFunc>* pht)
			:_node(node)
			,_pht(pht)
		{}

		Ref operator*()
		{
			return _node->_data;
		}

		Ptr operator->()
		{
			return &_node->_data;
		}

		Self& operator++()
		{
			if (_node->_next)
			{
				_node = _node->_next;
			}
			else
			{
				KeyOfT kot;
				HashFunc hf;
				
				size_t index = hf(kot(_node->_data)) % _pht->_tables.size();
				++index;
				while (index < _pht->_tables.size())
				{
					// 找下一个不为空的桶
					if (_pht->_tables[index])//找到则退出
						break;
					else
						++index;
				}

				// 表走完了，都没有找到下一个桶
				if (index == _pht->_tables.size())
					_node = nullptr;
				else//找到下一个桶
					_node = _pht->_tables[index];
			}
			return *this;
		}

		bool operator!=(const Self& s) const
		{
			return _node != s._node;
		}

		bool operator==(const Self& s) const
		{
			return _node == s._node;
		}
	};

	template<class K, class T, class KeyOfT , class HashFunc>
	class HashTable
	{
		typedef HashNode<T> Node;

		template<class K, class T, class Ref, class Ptr, class KeyOfT, class HashFunc>
		friend struct __HTIterator;

	public:
		typedef __HTIterator<K, T, T&, T*, KeyOfT, HashFunc> iterator;

	public:
		iterator begin()
		{
			for (size_t i = 0; i < _tables.size(); i++)
			{
				if (_tables[i])
					return iterator(_tables[i], this);
			}

			return end();
		}

		iterator end()
		{
			return iterator(nullptr , this);
		}

		bool Erase(const K& key)
		{
			if (_tables.empty())
				return false;

			HashFunc hf;
			size_t index = hf(key) % _tables.size();
			Node* prev = nullptr;
			Node* cur = _tables[index];
			KeyOfT kot;

			while (cur)
			{
				if (kot(cur->_data) == key)
				{
					if (prev == nullptr)
						_tables[index] = cur->_next;
					else
						prev->_next = cur->_next;

					delete cur;
					--_n;
					return true;
				}
				else
				{
					prev = cur;
					cur = cur->_next;
				}
			}

			return false;
		}

		iterator Find(const K& key)
		{
			if (_tables.empty())
			{
				return end();
			}

			HashFunc hf;
			size_t index = hf(key) % _tables.size();
			Node* cur = _tables[index];

			KeyOfT kot;
			while (cur)
			{
				if (kot(cur->_data) == key)//找到相应值
					return iterator(cur ,this);
				else
					cur = cur->_next;
			}
			return end();
		}

		size_t GetNextPrime(size_t num)//使用质数来进行扩容
		{
			static const unsigned long __stl_prime_list[28] =
			{
				53, 97, 193, 389, 769,
				1543, 3079, 6151, 12289, 24593,
				49157, 98317, 196613, 393241, 786433,
				1572869, 3145739, 6291469, 12582917, 25165843,
				50331653, 100663319, 201326611, 402653189, 805306457,
				1610612741, 3221225473, 4294967291
			};

			for (size_t i = 0; i < 28; ++i)
			{
				if (__stl_prime_list[i] > num)
				{
					return __stl_prime_list[i];
				}
			}

			return __stl_prime_list[27];
		}

		pair<iterator , bool> Insert(const T& data)
		{
			KeyOfT kot;
			iterator ret = Find(kot(data));
			if (ret != end())//不等于end()，则表示，在hashTable中有一样的数据，不能进行插入
				return make_pair(ret, false);

			HashFunc hf;
			// 负载因子 == 1时扩容
			if (_n == _tables.size())
			{
				size_t newSize = GetNextPrime(_tables.size());
				vector<Node*> newTables;
				newTables.resize(newSize);
				for (size_t i = 0; i < _tables.size(); i++)
				{
					Node* cur = _tables[i];
					while (cur)
					{
						Node* next = cur->_next;
						size_t index = hf(kot(cur->_data)) % newTables.size();
						cur->_next = newTables[index];
						newTables[index] = cur;

						cur = next;
					}
					_tables[i] = nullptr;
				}
				_tables.swap(newTables);
			}

			size_t index = hf(kot(data)) % _tables.size();
			Node* newNode = new Node(data);
			newNode->_next = _tables[index];
			_tables[index] = newNode;

			++_n;
			return make_pair(iterator(newNode , this) , false);
		}

	private:
		vector<Node*> _tables;
		size_t _n = 0;
	};

	/*void TestHashTable()
	{
		int a[] = { 4, 4, 24, 14,7,37,27,57,67,34,14,54 };
		HashTable<int, int> ht;
		for (auto e : a)
		{
			ht.Insert(make_pair(e, e));
		}
		ht.Insert(make_pair(84, 84));

	}*/
}

