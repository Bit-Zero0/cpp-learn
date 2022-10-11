#pragma once


enum color {
	RED,
	BLACK
};

template<class K , class V>
struct RBTreeNode
{
	RBTreeNode<K, V>* _left;
	RBTreeNode<K, V>* _right;
	RBTreeNode<K, V>* _parent;

	pair<K, V> _kv;
	color _col;

	RBTreeNode(const pair<K, V>& kv)
		:_left(nullptr)
		, _right(nullptr)
		, _parent(nullptr)
		, _kv(kv)
		, _col(RED)
	{}
};

template<class K , class V>
struct RBTree
{
	typedef RBTreeNode<K , V> Node;

public:
	RBTree()
		:_root (nullptr)
	{}

	bool Insert(const pair<K, V>& kv)
	{
		if (_root == nullptr)
		{
			_root = new Node(kv);
			_root->_col = BLACK;
			return true;
		}

		Node* parent = nullptr;
		Node* cur = _root;

		while (cur)
		{
			if (cur->_kv.first > kv.first)
			{
				parent = cur;
				cur = cur->_left;
			}
			else if (cur->_kv.first < kv.first)
			{
				parent = cur;
				cur = cur->_right;
			}
			else
			{
				return false;
			}
		}

		cur = new Node(kv);
		cur->_col = RED;
		if (parent->_kv.first > kv.first)
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

		return true;
	}

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
	
	void _InOrder(Node* root)
	{
		if (root == nullptr)
			return;

		_InOrder(root->_left);
		cout << root->_kv.first << " : " << root->_kv.second << endl;
		_InOrder(root->_right);
	}
	void InOrder()
	{
		_InOrder(_root);
	}


	bool IsBalance()
	{
		if (_root && _root->_col == RED)
		{
			cout << "根节点不是黑色" << endl;
			return false;
		}

		int banchMark = 0;
		Node* left = _root;
		while (left)
		{
			if (left->_col == BLACK)
				++banchMark;

			left = left->_left;
		}

		int blackNum = 0;
		return _IsBalance(_root, banchMark, blackNum);
	}
	bool _IsBalance(Node* root, int banchmark, int blacknum)
	{
		if (root == nullptr)
		{
			if (banchmark != blacknum)
			{
				cout << "存在路径黑色节点的数量不相等" << endl;
				return false;
			}

			return true;
		}

		if (root->_col == RED && root->_parent->_col == RED)
		{
			cout << "出现连续红色节点" << endl;
			return false;
		}

		if (root->_col == BLACK)
			++blacknum;

		return _IsBalance(root->_left, banchmark, blacknum)
			&& _IsBalance(root->_right, banchmark, blacknum);
	}

	int Height()
	{
		return _Height(_root);
	}

	int _Height(Node* root)
	{
		if (root == nullptr)
			return 0;
		int leftHeight = _Height(root->_left);
		int rightHeight = _Height(root->_right);

		return leftHeight > rightHeight ? leftHeight + 1 : rightHeight + 1;

	}

private:
	Node* _root;
};


void test_RBTree()
{
	RBTree<int, int> t;

	vector<int> v;
	//srand(time(0));

	int N = 100000000;
	for (int i = 0; i < N; i++)
	{
		v.push_back(i);
	}

	for (auto e : v)
	{
		t.Insert(make_pair(e,e));
	}

	//cout << "高度" << t.Height() << endl;
	

	/*int a[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14 };
	for (auto e : a)
	{
		t.Insert(make_pair(e, e));
		cout << "Insert " << e << ":" << t.IsBalance() << endl;
	}*/
}