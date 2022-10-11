#pragma once
using namespace std;



namespace K{
	template<class K>
	struct BSTreeNode {
		BSTreeNode* _left;
		BSTreeNode* _right;
		K _key;

		BSTreeNode(const K& key)
			:_left(nullptr)
			, _right(nullptr)
			, _key(key)
		{}
	};

	template <class K>
	struct BSTree {
		typedef BSTreeNode<K> Node;

	public:
		BSTree()
			:_root(nullptr)
		{}

		bool Insert(const K& key) {
			if (_root == nullptr)
			{
				_root = new Node(key);
				return true;
			}

			Node* parent = nullptr;
			Node* cur = _root;

			while (cur)
			{
				if (key < cur->_key)
				{
					parent = cur;
					cur = cur->_left;
				}
				else if (key > cur->_key)
				{
					parent = cur;
					cur = cur->_right;
				}
				else
				{
					return false;
				}
			}

			cur = new Node(key);
			if (key > parent->_key)
			{
				parent->_right = cur;
			}
			else
			{
				parent->_left = cur;
			}
			return true;
		}

		bool find(const K& key)
		{
			Node* cur = _root;
			while (cur)
			{
				if (cur->_key > key)
				{
					cur = cur->_left;
				}
				else if (cur->_key < key)
				{
					cur = cur->_right;
				}
				else {
					return true;
				}
			}
			return false;
		}

		bool Erase(const K& key)
		{
			Node* parent = nullptr;
			Node* cur = _root;

			while (cur)
			{
				if (cur->_key > key)
				{
					parent = cur;
					cur = cur->_left;
				}
				else if (cur->_key < key)
				{
					parent = cur;
					cur = cur->_right;
				}
				else
				{
					if (cur->_left == nullptr)
					{
						if (parent == nullptr)
						{
							_root = cur->_right;
						}
						else
						{
							if (parent->_left == cur)
								parent->_left = cur->_right;
							else
								parent->_right = cur->_right;
						}
						delete cur;
					}
					else if (cur->_right == nullptr)
					{
						if (parent == nullptr)
						{
							_root = cur->_left;
						}
						else
						{
							if (parent->_left == cur)
								parent->_left = cur->_left;
							else
								parent->_right = cur->_left;
						}
						delete cur;
					}
					else
					{
						Node* minParent = cur;
						Node* min = cur->_right;

						while (min->_left)
						{
							minParent = min;
							min = min->_left;
						}

						cur->_key = min->_key;

						if (minParent->_left == min)
							minParent->_left = min->_right;
						else
							minParent->_right = min->_right;

						delete min;
					}

					return true;
				}
			}

			return false;
		}

		void InOrder()
		{
			_InOrder(_root);
			cout << endl;
		}

		bool InsertR(const K& key)
		{
			return _InsertR(_root, key);
		}

		Node* FindR(const K& key)
		{
			return _FindR(_root, key);
		}

		bool EraseR(const K& key)
		{
			return _EraseR(_root, key);
		}

	private:
		Node* _root;

		bool _EraseR(Node*& root, const K& key)
		{
			if (root == nullptr)
				return false;

			if (root->_key > key)
			{
				return _EraseR(root->_left, key);
			}
			else if (root->_key < key)
			{
				return _EraseR(root->_right, key);
			}
			else
			{
				Node* del = root;
				if (root->_left == nullptr)
					root = root->_right;
				else if (root->_right == nullptr)
					root = root->_left;

				delete del;
			}
		}

		bool _InsertR(Node*& root, const K& key)
		{
			if (root == nullptr)
			{
				root = new Node * (key);
				return true;
			}

			if (root->_key > key)
				return _InsertR(root->_left, key);
			else if (root->_key < key)
				return _InsertR(root->_right, key);
			else
				return false;
		}

		Node* _FindR(Node* root, const K& key)
		{
			if (root == nullptr)
				return nullptr;

			if (root->_key < key)
				return _FindR(root->_right, key);
			else if (root->_key > key)
				return _FindR(root->_left, key);
			else
				return root;
		}

		void _InOrder(Node* root)
		{
			if (root == nullptr)
			{
				return;
			}
			_InOrder(root->_left);
			cout << root->_key << " ";
			_InOrder(root->_right);
		}


	};
}



namespace KV {
	template<class K ,class V>
	struct BSTreeNode {
		/*BSTreeNode<K ,V>* _left;
		BSTreeNode<K,V>* _right;*/
		BSTreeNode* _left;
		BSTreeNode* _right;
		K _key;
		V _value;

		BSTreeNode(const K& key , const V& value)
			:_left(nullptr)
			, _right(nullptr)
			, _key(key)
			,_value(value)
		{}
	};

	template <class K , class V>
	struct BSTree {
		typedef BSTreeNode<K , V> Node;

	public:
		BSTree()
			:_root(nullptr)
		{}

		bool Insert(const K& key, const V& value) {
			if (_root == nullptr)
			{
				_root = new Node(key ,value);
				return true;
			}

			Node* parent = nullptr;
			Node* cur = _root;

			while (cur)
			{
				if (key < cur->_key)
				{
					parent = cur;
					cur = cur->_left;
				}
				else if (key > cur->_key)
				{
					parent = cur;
					cur = cur->_right;
				}
				else
				{
					return false;
				}
			}

			cur = new Node(key , value);
			if (key > parent->_key)
			{
				parent->_right = cur;
			}
			else
			{
				parent->_left = cur;
			}
			return true;
		}

		Node* Find(const K& key) //这里将 返回值从bool改为了 Node* ， 因为是需要返回一个我们找到的节点
		{
			Node* cur = _root;
			while (cur)
			{
				if (cur->_key > key)
				{
					cur = cur->_left;
				}
				else if (cur->_key < key)
				{
					cur = cur->_right;
				}
				else {
					return cur; //返回我们找到的节点
				}
			}
			return nullptr;
		}

		bool Erase(const K& key)
		{
			Node* parent = nullptr; 
			Node* cur = _root;

			while (cur)
			{
				if (cur->_key > key)
				{
					parent = cur;
					cur = cur->_left;
				}
				else if (cur->_key < key)
				{
					parent = cur;
					cur = cur->_right;
				}
				else
				{
					if (cur->_left == nullptr)
					{
						if (parent == nullptr)
						{
							_root = cur->_right;
						}
						else
						{
							if (parent->_left == cur)
								parent->_left = cur->_right;
							else
								parent->_right = cur->_right;
						}
						delete cur;
					}
					else if (cur->_right == nullptr)
					{
						if (parent == nullptr)
						{
							_root = cur->_left;
						}
						else
						{
							if (parent->_left == cur)
								parent->_left = cur->_left;
							else
								parent->_right = cur->_left;
						}
						delete cur;
					}
					else
					{
						Node* minParent = cur;
						Node* min = cur->_right;

						while (min->_left)
						{
							minParent = min;
							min = min->_left;
						}

						cur->_key = min->_key;

						if (minParent->_left == min)
							minParent->_left = min->_right;
						else
							minParent->_right = min->_right;

						delete min;
					}

					return true;
				}
			}

			return false;
		}

		void InOrder()
		{
			_InOrder(_root);
			cout << endl;
		}

	private:
		Node* _root;


		void _InOrder(Node* root)
		{
			if (root == nullptr)
				return;

			_InOrder(root->_left);
			cout << root->_key << ":" << root->_value << endl;
			_InOrder(root->_right);
		}
	};
}



void TestBSTree1()
{
	K::BSTree<int> t;
	int a[] = { 5, 3, 4, 1, 7, 8, 2, 6, 0, 9,5,5 };
	for (auto e : a)
	{
		t.Insert(e);
	}
	t.InOrder();
	cout << endl << t.find(0) << endl;

	t.Erase(5);
	t.InOrder();

	t.Erase(2);
	t.InOrder();

}



void wordTree() {
	KV::BSTree<string, string> dict;
	dict.Insert("sort", "排序");
	dict.Insert("left", "左边");
	dict.Insert("right", "右边");
	dict.Insert("map", "地图、映射");
	
	string str;
	while (cin >> str) {
		KV::BSTreeNode<string, string>* ret = dict.Find(str);
		if (ret)
			cout << "对应的中文解释：" << ret->_value << endl;
		else
			cout << "无此单词" << endl;
	}
}


void TestBSTree2() {
	string arr[] = { "苹果", "西瓜","草莓", "苹果", "西瓜", "苹果", "苹果", "西瓜", "苹果", "香蕉", "苹果", "香蕉" };
	KV::BSTree<string, int> countTree;
	for (auto& str : arr)
	{
		auto ret = countTree.Find(str);
		if (ret != nullptr) //如果水果树中存在此水果，则数量+1.
			ret->_value++;
		else
			countTree.Insert(str, 1);  //若水果树中没有此水果则在水果树中加入此水果。
	}
	countTree.InOrder();
}
