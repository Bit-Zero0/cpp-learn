#pragma once


enum color {
	RED,
	BLACK
};

template<class T>
struct RBTreeNode
{
	RBTreeNode<T>* _left;
	RBTreeNode<T>* _right;
	RBTreeNode<T>* _parent;

	T _data;
	color _col;

	RBTreeNode(const T& data)
		:_left(nullptr)
		, _right(nullptr)
		, _parent(nullptr)
		, _col(RED)
		, _data(data)
	{}
};


template<class T, class Ref, class Ptr>
struct RBTreeIterator
{
	typedef RBTreeNode<T> Node;
	typedef RBTreeIterator<T, Ref, Ptr> Self;
	Node* _node;

	RBTreeIterator(Node* node)
		:_node(node)
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
		if (_node->_right)
		{
			Node* min = _node->_right;
			while (min->_left)
			{
				min = min->_left;
			}
			_node = min;
		}
		else
		{
			Node* cur = _node;
			Node* parent = cur->_parent;

			while (parent && cur == parent->_right)
			{
				cur = parent;
				parent = parent->_parent;
			}
			_node = parent;
		}
		return *this;
	}

	Self& operator--() 
	{
		if (_node->_left)
		{
			Node* max = _node->_left;
			while (max)
			{
				max = max->_right;
			}
			_node = max;
		}
		else
		{
			Node* cur = _node;
			Node* parent = cur->_parent;
			while (parent && cur == parent->_left)
			{
				cur = parent;
				parent = parent->_parent;
			}
			_node = parent;
		}

		return *this;
	}

	bool operator!=(const Self& s) const 
	{
		return _node != s._node;
	}

	bool operator== (const Self& s) const
	{
		return _node = s._node;
	}

};


template<class K , class T , class KeyOfT>
struct RBTree
{
	typedef RBTreeNode<T> Node;

public:
	typedef RBTreeIterator<T, T&, T*> iterator;
	typedef RBTreeIterator<T, const T&, const T*> const_iterator;

	RBTree()
		:_root (nullptr)
	{}

	RBTree(const RBTree<K, T, KeyOfT>& t)
	{
		_root = Copy(t._root);
	}

	~RBTree()
	{
		Destroy(_root);
		_root == nullptr;
	}

	iterator begin()
	{
		Node* min = _root;
		while (min && min->_left)
		{
			min = min->_left;
		}

		return iterator(min);
	}

	iterator end()
	{
		return iterator(nullptr);
	}

	iterator Find(const K& key)
	{
		Node* cur = _root;
		KeyOfT kot;
		while (cur)
		{
			if (kot(cur->_data) > key)
			{
				cur = cur->_left;
			}
			else if (kot(cur->_data) < key)
			{
				cur = cur->_right;
			}
			else
			{
				return iterator(cur);
			}
		}

		return end();
	}

	RBTree<K, T, KeyOfT>& operator=(RBTree<K, T, KeyOfT> t)
	{
		swap(_root, t._root);
		return *this;
	}

	pair<iterator , bool> Insert(const T& data)
	{
		if (_root == nullptr)
		{
			_root = new Node(data);
			_root->_col = BLACK;
			return make_pair(iterator(_root) , true);
		}

		KeyOfT kot;

		Node* parent = nullptr;
		Node* cur = _root;

		while (cur)
		{
			if (kot(cur->_data) > kot(data))
			{
				parent = cur;
				cur = cur->_left;
			}
			else if (kot(cur->_data) < kot(data))
			{
				parent = cur;
				cur = cur->_right;
			}
			else
			{
				return make_pair(iterator(cur),false);
			}
		}

		cur = new Node(data);
		Node* NewNode = cur;
		cur->_col = RED;
		if (kot(parent->_data) > kot(data))
		{
			parent->_left = cur;
			cur->_parent = parent;
		}
		else
		{
			parent->_right = cur;
			cur->_parent = parent;
		}


		while (parent && parent->_col == RED)
		{
			Node* GrandFather = parent->_parent;
			if (parent == GrandFather->_left)
			{
				Node* uncle = GrandFather->_right;

				if (uncle && uncle->_col == RED)
				{
					parent->_col = uncle->_col = BLACK;
					GrandFather->_col = RED;

					cur = GrandFather;
					parent = cur->_parent;
				}
				else 
				{
					if (cur == parent->_left)
					{
						RotateR(GrandFather);
						parent->_col = BLACK;
						GrandFather->_col = RED;
					}
					else
					{
						RotateL(parent);
						RotateR(GrandFather);
						cur->_col = BLACK;
						GrandFather->_col = RED;
					}

					break;
				}
			}
			else
			{
				Node* uncle = GrandFather->_left;
				if (uncle && uncle->_col == RED)
				{
					parent->_col = uncle->_col = BLACK;
					GrandFather->_col = RED;

					cur = GrandFather;
					parent = cur->_parent;
				}
				else
				{
					if (cur == parent->_right)
					{
						RotateL(GrandFather);
						parent->_col = BLACK;
						GrandFather->_col = RED;
					}
					else
					{
						RotateR(parent);
						RotateL(GrandFather);

						cur->_col = BLACK;
						GrandFather->_col = RED;
					}
					
					break;
				}
			}
		}

		_root->_col = BLACK;

		return make_pair(iterator(NewNode) , true);
	}
private:
	void RotateR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;

		parent->_left = subLR;
		if (subLR)
			subLR->_parent = parent;

		Node* parentParent = parent->_parent;

		subL->_right = parent;
		parent->_parent = subL;

		if (_root == parent)
		{
			_root = subL;
			subL->_parent = nullptr;
		}
		else
		{
			if (parentParent->_left == parent)
				parentParent->_left = subL;
			else
				parentParent->_right = subL;

			subL->_parent = parentParent;
		}
	}

	void RotateL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;

		parent->_right = subRL;

		if (subRL)
			subRL->_parent = parent;

		Node* parentParent = parent->_parent;

		subR->_left = parent;
		parent->_parent = subR;

		if (_root == parent)
		{
			_root = subR;
			subR->_parent = nullptr;
		}
		else
		{
			if (parentParent->_left == parent)
				parentParent->_left = subR;
			else
				parentParent->_right = subR;

			subR->_parent = parentParent;
		}
	}
	

	void Destroy(Node* root)
	{
		if (root == nullptr)
		{
			return;
		}

		Destroy(root->_left);
		Destroy(root->_right);
		delete root;
	}

	Node* Copy(Node* root)
	{
		if (root == nullptr)
			return nullptr;

		//¸¸Ç×Á´½Óº¢×Ó
		Node* newRoot = new Node(root->_data);
		newRoot->_left = Copy(root->_left);
		newRoot->_right = Copy(root->_right);

		//º¢×ÓÁ´½Ó¸¸Ç×
		if (newRoot->_left)
			newRoot->_left->_parent = newRoot;
		if (newRoot->_right)
			newRoot->_right->_parent = newRoot;

		return newRoot;
		
	}
private:
	Node* _root;
};
