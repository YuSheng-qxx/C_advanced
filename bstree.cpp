#include<windows.h>
#include<iostream>
using namespace std;
template <class T>
struct BSTNode
{
	T _data;
	BSTNode<T>* _left;
	BSTNode<T>* _right;

	BSTNode(const T& val = T())
		:_data(val)
		, _left(nullptr)
		, _right(nullptr)
	{}
};

//ʵ�֣�������С�ڸ������������ڸ�
template <class T>
class BSTree
{
public:
	typedef BSTNode<T> Node;

	BSTree()
		:_root(nullptr)
	{}

	Node* find(const T& val)
	{
		int count = 0;
		if (_root == nullptr)
			return _root;
		Node* cur = _root;
		while (cur)
		{
			++count;
			if (cur->_data == val)
				return cur;
			else if (cur->_data > val)
			{
				cur = cur->_left;
			}
			else
			{
				cur = cur->_right;
			}
		}
		cout << "count:" << count << endl;
		return nullptr;
	}

	bool insert(const T& val)
	{
		if (_root == nullptr)
		{
			//�������������ڵ�
			_root = new Node(val);
			return true;
		}
		Node* cur = _root;
		Node* parent = nullptr;
		while (cur)
		{
			parent = cur;
			if (cur->_data == val)
				return false;//����ʧ��
			else if (cur->_data > val)
			{
				cur = cur->_left;
			}
			else
			{
				cur = cur->_right;
			}
		}
		//�����½ڵ�
		cur = new Node(val);
		//����
		if (parent->_data > val)
			parent->_left = cur;
		else
			parent->_right = cur;
		return true;
	}

	void inorder()
	{
		_inorder(_root);
		cout << endl;
	}

	void _inorder(Node* root)
	{
		if (root)
		{
			_inorder(root->_left);
			cout << root->_data << " ";
			_inorder(root->_right);
		}
	}

	bool erase(const T& val)
	{
		if (_root == nulptr)
			return false;
		Node* cur = _root;
		Node* parent = nullptr;
		while (cur)
		{
			if (cur->_data == val)
				break;
			else if (cur->_data > val)
			{
				parent = cur;
				cur = cur->_left;
			}
			else
			{
				parent = cur;
				cur = cur->_right;
			}
		}
		//���ݲ�����
		if (cur == nullptr)
			return false;
		//ɾ��
		//1.Ҷ��
		if (cur->_left == nullptr && cur->_right == nullptr)
		{
			//�Ƿ�Ϊ���ڵ�
			if (cur != _root)
			{
				if (parent->_left == cur)
					parent->_left = nullptr;
				else
					parent->_right = nullptr;
			}
			else
				_root = nullptr;
			delete cur;
		}
		//��Ҷ�ӣ����Ӳ�����
		else if (cur->_left == nullptr)
		{
			if (cur != _root)
			{
				if (parent->_left == cur)
					parent->_left = cur->_right;
				else
					parent->_right = cur->_right;
			}
			else
			{
				_root = cur->_right;
			}
			delete cur;
		}
		//�Һ��Ӳ�����
		else if (cur->_right == nullptr)
		{
			if (cur != _root)
			{
				if (parent->_left == cur)
					parent->_left = cur->_left;
				else
					parent->_right = cur->_left;
			}
			else
			{
				_root = cur->_left;
			}
			delete cur;
		}
		//���Һ��Ӷ�����
		else
		{
			//���������ҽڵ�
			Node* mostRight = cur->_left;
			parent = cur;
			while (mostRight->_right)
			{
				parent = mostRight;
				mostRight = mostRight->_right;
			}
			//���ҽڵ��ֵ�����ɾ���Ľڵ�cur
			cur->_data = mostRight->_data;
			//ɾ�����ҽڵ�
			if (parent->_left==mostRight)
				parent->_left = mostRight->_left;
			else
				parent->_right = mostRight->_left;
			delete mostRight;

			/*   ��ѡһ
			//�Һ�������ڵ�
			Node* mostLeft = cur->_right;
			parent = cur;
			while (mostLeft->_left)
			{
				parent = mostLeft;
				mostLeft = mostLeft->_left;
			}
			cur->_data = mostLeft->_data;
			if (parent->_left == mostLeft)
				parent->_left = mostLeft->_right;
			else
				parent->_right = mostLeft->_right;
			delete mostLeft;
			*/
		}
	}

	Node* copyTree(Node* root)
	{
		if (root)
		{
			Node* node = new Node(root->_data);
			node->_left = copyTree(root->_left);
			node->_right = copyTree(root->_right);
			return node;
		}
		return nullptr;
	}


	BSTree(const BSTree<T>& bst)
	{
		_root = copyTree(bst._root);
	}

	BSTree<T>& operator=(const BSTree<T>& bst)
	{
		if (this != &bst)
		{
			destory(_root);
			_root = copyTree(bst._root);
		}
		return *this;
	}

	/*BSTree<T>& operator=(const BSTree<T> bst)
	{
		swap(_root, bst._root);
		return *this;
	}*/

	void destory(Node* root)
	{
		if (root)
		{
			destory(root->_left);
			destory(root->_right);
			delete root;
		}
	}

	~BSTree()
	{
		destory(_root);
		_root = nullptr;
	}

private:
	Node* _root = nullptr;
};

void test()
{
	BSTree<int> b;
	b.insert(5);
	b.insert(15);
	b.insert(4);
	b.insert(9);
	b.insert(0);
	b.inorder();
	BSTree<int> copy(b);
	copy.inorder();
}

int main()
{
	test();
	system("pause");
	return 0;
}