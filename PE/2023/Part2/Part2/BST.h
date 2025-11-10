#pragma once
#include <iostream>
using namespace std;

template <class T>
class BinarySearchTree;

template <class T>
class TreeNode {
private:
	T _item;
	TreeNode<T>* _left;
	TreeNode<T>* _right;
	int _height;
	int _weight; // new addition
public:
	TreeNode(T x) { _left = _right = NULL; _item = x; _height = 0; _weight = 1; };

	friend BinarySearchTree<T>;
};

template <class T>
class BinarySearchTree {
protected:
	int _size;
	TreeNode<T>* _root;
	void _printTree(int indent, TreeNode<T>*, bool withHeightAndWeight);

	// The following functions are optional for you to implement. 
	TreeNode<T>*  _insert(TreeNode<T>* current, T x);
	void _inOrderPrint(TreeNode<T>*);
	void _postOrderPrint(TreeNode<T>*);
	void _preOrderPrint(TreeNode<T>*);
	TreeNode<T>* _rightRotation(TreeNode<T>*);
	TreeNode<T>* _leftRotation(TreeNode<T>*);
	TreeNode<T>* _searchMax(TreeNode<T>*);
	TreeNode<T>* _searchMin(TreeNode<T>*);
	TreeNode<T>* _search(TreeNode<T>*, T);
	void _destroySubTree(TreeNode<T>*);

	int height(TreeNode<T>* node) {
		return node ? node->_height : -1;
	}

	int weight(TreeNode<T>* node) {
		return node ? node->_weight : 0;
	}

	int getBalance(TreeNode<T>* node) {
		return node ? height(node->_left) - height(node->_right) : 0;
	}

	void updateNode(TreeNode<T>* node) {
		if (node) {
			node->_height = 1 + std::max(height(node->_left), height(node->_right));
			node->_weight = 1 + weight(node->_left) + weight(node->_right);
		}
	}


public:
	BinarySearchTree() { _root = NULL; _size = 0; }
	~BinarySearchTree();
	int size() { return _size; };
	void insert(T);
	void printTree(bool withHeightAndWeight = 1);
	void inOrderPrint();
	void postOrderPrint();
	void preOrderPrint();
	T searchMax() { return T(); }; 
	T searchMin() { return T(); };
	bool exist(T x) { return T(); };
	T search(T x) { return T(); };
	T successor(T);

	int rank(const T& x);
	T select(int rank);

};



template <class T>
void BinarySearchTree<T>::insert(T x)
{
	_root = _root ? _insert(_root, x) : new TreeNode<T>(x);
	if (_size == 0) _size++;
}

template <class T>
void BinarySearchTree<T>::_printTree(int indent, TreeNode<T>* node, bool withHeightAndWeight) {

	if (!node)
		return;

	if (node->_right)
		_printTree(indent + 2, node->_right, withHeightAndWeight);
	for (int i = 0; i < indent; i++)
		cout << "  ";
	cout << node->_item;
	if (withHeightAndWeight)
		cout << "(h=" << node->_height << ",w=" << node->_weight << ")";
	cout << endl;
	if (node->_left)
		_printTree(indent + 2, node->_left, withHeightAndWeight);


};

template <class T>
void BinarySearchTree<T>::printTree(bool withHeightAndWeight) {
	_printTree(0, _root, withHeightAndWeight);
}


template <class T>
void BinarySearchTree<T>::preOrderPrint() {

	_preOrderPrint(_root);
	cout << endl;
}


template <class T>
void BinarySearchTree<T>::_preOrderPrint(TreeNode<T>* node) {
	if (!node) return;
	cout << node->_item << " ";
	_preOrderPrint(node->_left);
	_preOrderPrint(node->_right);
}


template <class T>
void BinarySearchTree<T> ::_destroySubTree(TreeNode<T>* node)
{
	if (node->_left)
		_destroySubTree(node->_left);
	if (node->_right)
		_destroySubTree(node->_right);
	delete node;
}

template <class T>
BinarySearchTree<T> :: ~BinarySearchTree()
{
	if (_root)
		_destroySubTree(_root);
}



template <class T>
void BinarySearchTree<T>::inOrderPrint() {
}


template <class T>
void BinarySearchTree<T>::_inOrderPrint(TreeNode<T>* node) {
}


template <class T>
void BinarySearchTree<T>::postOrderPrint() {
}


template <class T>
void BinarySearchTree<T>::_postOrderPrint(TreeNode<T>* node) {
}

template <class T>
TreeNode<T>* BinarySearchTree<T>::_insert(TreeNode<T>* current, T x) {


	if (current->_item > x)
	{
		if (current->_left)
			current->_left = _insert(current->_left, x);
		else
		{
			current->_left = new TreeNode<T>(x);
			_size++;
		}
	}
	else if (x > current->_item) {
		if (current->_right)
			current->_right = _insert(current->_right, x);
		else
		{
			current->_right = new TreeNode<T>(x);
			_size++;
		}
	}
	else
		return current; // When the node already existed in the tree

	updateNode(current);
	int balance = getBalance(current);
	if (balance > 1 && x <= current->_left->_item) {
		return _rightRotation(current);
	}
	else if (balance < -1 && x >= current->_right->_item) {
		return _leftRotation(current);
	}
	else if (balance > 1 && x > current->_left->_item) {
		current->_left = _leftRotation(current->_left);
		return _rightRotation(current);
	}
	else if (balance < -1 && x < current->_right->_item) {
		current->_right = _rightRotation(current->_right);
		return _leftRotation(current);
	}
	else {
		return current;
	}
}

template <class T>
TreeNode<T>* BinarySearchTree<T>::_searchMax(TreeNode<T>* current) {
	return current;
}


template <class T>
TreeNode<T>* BinarySearchTree<T>::_searchMin(TreeNode<T>* current) {
	return current;
}

template <class T>
TreeNode<T>* BinarySearchTree<T>::_search(TreeNode<T>* current, T x) {
	return NULL;
}


template <class T>
T BinarySearchTree<T>::successor(T x)
{
	return T();
}

template <class T>
TreeNode<T>* BinarySearchTree<T>::_leftRotation(TreeNode<T>* node)
{
	if (!node || !node->_right) {
		return node;
	}
	TreeNode<T>* temp = node->_right;
	node->_right = temp->_left;
	temp->_left = node;
	updateNode(node);
	updateNode(temp);
	return temp;
}

template <class T>
TreeNode<T>* BinarySearchTree<T>::_rightRotation(TreeNode<T>* node)
{
	if (!node || !node->_left) {
		return node;
	}
	TreeNode<T>* temp = node->_left;
	node->_left = temp->_right;
	temp->_right = node;
	updateNode(node);
	updateNode(temp);
	return temp;
}

template <class T>
int  BinarySearchTree<T>::rank(const T& x)
{
	if (!_size) {
		return -1;
	}
	else {
		TreeNode<T>* cur = _root;
		int Rank = 0;
		while (cur) {
			if (cur->_item == x) {
				if (cur->_left) {
					return cur->_left->_weight + 1 + Rank;
				}
				else {
					return 1 + Rank;
				}
			}
			else if (cur->_item > x) {
				if (!cur->_left) {
					return -1;
				}
				else {
					cur = cur->_left;
				}
			}
			else {
				if (!cur->_right) {
					return -1;
				}
				else {
					if (cur->_left) {
						Rank += cur->_left->_weight + 1;
					}
					else {
						Rank++;
					}
					cur = cur->_right;
				}
			}
		}
		return -1;
	}
}

template <class T>
T  BinarySearchTree<T>::select(int rank)
{
	TreeNode<T>* cur = _root;
	if (_size == 1) {
		return cur->_item;
	}
	else if (_size == 2 && !cur->_left) {
		if (rank == 1) {
			return cur->_item;
		}
		else {
			return cur->_right->_item;
		}
	}
	else {
		int Rank = 0;
		while (cur) {
			if (cur->_left) {
				if (Rank + cur->_left->_weight + 1 > rank) {
					cur = cur->_left;
				}
				else if (Rank + cur->_left->_weight + 1 < rank) {
					Rank += cur->_left->_weight + 1;
					cur = cur->_right;
				}
				else {
					return cur->_item;
				} 
			}
			else {
				if (Rank + 1 < rank) {
					Rank ++;
					cur = cur->_right;
				}
				else {
					return cur->_item;
				}
			}
		}
	}
}
