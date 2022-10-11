#pragma once

#include <iostream>
#include <assert.h>
#include "reverse_iterator.h"


namespace fmy
{
	template <class T>
	struct ListNode
	{
		ListNode<T>* _next;
		ListNode<T>* _prev;
		T _data;

		ListNode(const T& data = T())
			:_next(nullptr)
			, _prev(nullptr)
			, _data(data)
		{}
	};


	template <class T , class Ref , class Ptr>
	struct __list_iterator
	{
		typedef ListNode<T> Node;
		typedef __list_iterator<T, Ref, Ptr> self;
		Node* _node;

		__list_iterator(Node* x)
			:_node(x)
		{}

		//Ref 是 const T& 或 T&
		Ref operator*()
		{
			return _node -> _data;
		}

		//ptr 是 const T* 或 T*
		Ptr operator->()
		{
			return &_node->_data;
		}

		//++int
		self& operator++()
		{
			_node = _node->_next;
			return *this;
		}
		//int++
		self operator++(int)
		{
			self tmp(*this);
			_node = _node->_next;
			return tmp;
		}

		//--int
		self& operator--()
		{
			_node = _node->_prev;
			return *this;
		}

		// int--
		self operator--(int)
		{
			self tmp(*this);
			_node = _node->_prev;
			return tmp;
		}

		bool operator!=(const self& it) const
		{
			return _node != it._node;
		}

		bool operator==(const self& it) const
		{
			return _node == it._node;
		}
	};

	template<class T>
	class list
	{
		typedef ListNode<T> Node;

	public:
		typedef __list_iterator<T , T& , T*> iterator; //这是普通的迭代器
		typedef __list_iterator<T, const T&, const T*> const_iterator; //这是const迭代器

		typedef reverse_iterator<const_iterator, const T&, const T*> const_reverse_iterator;
		typedef reverse_iterator<iterator, T&, T*>  reverse_iterator;
		

		reverse_iterator rbegin()
		{
			return reverse_iterator(end());
		}

		reverse_iterator rend()
		{
			return reverse_iterator(begin());
		}

		iterator begin() //因为 _head->_next 是指针，所以iterator放回的是一个 T*
		{
			return iterator(_head->_next);
		}

		iterator end()//因为 _head是指针，所以iterator放回的是一个 T*
		{
			return iterator(_head);
		}

		const_iterator begin() const//因为 _head->_next 是指针，但const_iterator是const修饰的，所以返回的是一个 const T*
		{
			return const_iterator(_head->_next);
		}

		const_iterator end() const//因为 _head 是指针，但const_iterator是const修饰的，所以返回的是一个 const T*
		{
			return const_iterator(_head);
		}

		list()
		{
			_head = new Node();
			_head->_next = _head;
			_head->_prev = _head;
		}

		////传统写法 lt2(lt1)
		//list(const list<T>& lt)
		//{
		//	_head = new Node();
		//	_head->_next = _head;
		//	_head->_prev = _head;

		//	for (auto e : lt)
		//	{
		//		push_back(e);
		//	}
		//}
		////lt2 = lt1
		//list<T>& operator=(const list<T>& lt)
		//{
		//	if (this != &lt)
		//	{
		//		clear();
		//		for (auto e : lt)
		//		{
		//			push_back(e);
		//		}
		//	}

		//	return *this;
		//}


		list(int n, const T& val = T())
		{
			_head = new Node();
			_head->_next = _head;
			_head->_prev = _head;
			for (int i = 0; i < n; i++)
			{
				push_back(val);
			}
		}
		list(size_t n, const T& val = T())
		{
			_head = new Node();
			_head->_next = _head;
			_head->_prev = _head;
			for (size_t i = 0; i < n; i++)
			{
				push_back(val);
			}
		}
		//现代写法
		template<class InputIterator>
		list(InputIterator first, InputIterator last )
		{
			_head = new Node();
			_head->_next = _head;
			_head->_prev = _head;

			while (first != last)
			{
				push_back(*first);
				++first;
			}
		}
		list(const list<T>& lt)
		{
			_head = new Node();
			_head->_next = _head;
			_head->_prev = _head;

			list<T> tmp(lt.begin(), lt.end());
			std::swap(_head, tmp._head);
		}

		list<T>& operator=(list<T> lt)
		{
			std::swap(_head, lt._head);
			return *this;
		}

		~list()
		{
			clear();

			delete _head;
			_head = nullptr;
		}

		


		void clear()
		{

			/*iterator it = begin();
			while (it != end())
			{
				iterator del = it++;
				delete del._node;
			}

			_head->_next = _head;
			_head->_prev = _head;*/


			iterator lt = begin();
			while (lt != end())
			{
				erase(lt++);
			}
		}


		void push_front(const T& x)
		{
			insert(begin(), x);
		}

		void pop_front()
		{
			erase(begin());
		}


		iterator insert(iterator pos , const T& x)
		{
			Node* cur = pos._node;
			Node* prev = cur->_prev;
			Node* NewNode = new Node(x);

			prev->_next = NewNode;
			NewNode->_prev = prev;
			NewNode->_next = cur;
			cur->_prev = NewNode;

			return iterator(NewNode);
		}

		void push_back(const T& x)
		{
			/*Node* tail = _head->_prev;
			Node* NewNode = new Node(x);
			tail->_next = NewNode;
			NewNode->_prev = tail;
			NewNode->_next = _head;
			_head->_prev = NewNode;*/

			insert(end(), x);
		}


		void pop_back()
		{
			erase(--end());
		}


		iterator erase(iterator pos)
		{
			assert(pos != end());

			Node* prev = pos._node->_prev;
			Node* next = pos._node->_next;
			delete pos._node;
			prev->_next = next;
			next->_prev = prev;

			return iterator(next); //返回的是删除节点的下一个节点
		}


	private:
		Node* _head;
	};


	void print_list(const list<int>& lt)
	{
		list<int>::const_iterator it = lt.begin();
		while (it != lt.end())
		{
			//*it = 10;
			std::cout << *it << " ";
			++it;
		}
		std::cout << std::endl;
	}


}
