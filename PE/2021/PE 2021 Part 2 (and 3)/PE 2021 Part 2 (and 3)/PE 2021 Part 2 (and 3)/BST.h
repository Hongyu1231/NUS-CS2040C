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
	T _sst; // sum of the all the nodes in its subtree with itself as the root
public:
	TreeNode(T x) { _left = _right = NULL; _item = x; _height = 0; _sst = x; };
	friend BinarySearchTree<T>;
	friend class MagicalPancakeGym;
};

template <class T>
class BinarySearchTree {
private:
	bool _balancing; 
	// true: the tree will be balanced as an AVL tree mentioned in our lecture
	// false: the tree will not do any rotation to balance itself

	int _size;
	TreeNode<T>* _root;
	void _printTree(int indent, TreeNode<T>*, bool withSST);
	void _preOrderPrint(TreeNode<T>*);
	void _inOrderPrint(TreeNode<T>*);
	void _postOrderPrint(TreeNode<T>*);
	TreeNode<T>* _insert(TreeNode<T>* current, T x);
    void _destroySubTree(TreeNode<T>*);

	int height(TreeNode<T>* node) {
		return node ? node->_height : -1;
	}

	T sst(TreeNode<T>* node) {
		return node ? node->_sst : 0;
	}

	int getBalance(TreeNode<T>* node) {
		return node ? height(node->_left) - height(node->_right) : 0;
	}

	void updateNode(TreeNode<T>* node) {
		if (node) {
			node->_height = std::max(height(node->_left), height(node->_right)) + 1;
			node->_sst = node->_item + sst(node->_left) + sst(node->_right);
		}
	}

	TreeNode<T>* _leftRotation(TreeNode<T>* node) {
		if (!node || !node->_right) {
			return node;
		}
		else {
			TreeNode<T>* temp = node->_right;
			node->_right = temp->_left;
			temp->_left = node;
			updateNode(node);
			updateNode(temp);
			return temp;
		}
	}

	TreeNode<T>* _rightRotation(TreeNode<T>* node) {
		if (!node || !node->_left) {
			return node;
		}
		else {
			TreeNode<T>* temp = node->_left;
			node->_left = temp->_right;
			temp->_right = node;
			updateNode(node);
			updateNode(temp);
			return temp;
		}
	}


public:
	BinarySearchTree(bool balancing=false) { _root = NULL; _size = 0; _balancing = balancing; }
	~BinarySearchTree();
	int size() { return _size; };
	void insert(T);
	void printTree(bool withSST = true); 
	// if withSST==true, it will print the sum of subtree also

	void inOrderPrint();
	void postOrderPrint();
	void preOrderPrint();

	T sumLE(T n);
	friend class MagicalPancakeGym;
};




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
		return current;

	updateNode(current);
	if (_balancing) {
		int balance = getBalance(current);
		if (balance > 1 && x <= current->_left->_item) {
			return _rightRotation(current);
		}
		else if (balance > 1 && x > current->_left->_item) {
			current->_left = _leftRotation(current->_left);
			return _rightRotation(current);
		}
		else if (balance < -1 && x >= current->_right->_item) {
			return _leftRotation(current);
		}
		else if (balance < -1 && x < current->_right->_item) {
			current->_right = _rightRotation(current->_right);
			return _leftRotation(current);
		}
	}
	return current;
}

template <class T>
void BinarySearchTree<T>::insert(T x) {

	if (_root == NULL)
	{
		_root = new TreeNode<T>(x);
		_size++;
	}
	else
		_root = _insert(_root, x);

}




template <class T>
void BinarySearchTree<T>::printTree(bool withHeight) {
	_printTree(0, _root, withHeight);
}

template <class T>
T BinarySearchTree<T>::sumLE(T n)
{
	if (!_size) {
		return 0;
	}
	else {
		TreeNode<T>* cur = _root;
		T sum = 0;
		while (cur) {
			if (cur->_item == n) {
				return cur->_item + sst(cur->_left) + sum;
			}
			else if (cur->_item > n) {
				cur = cur->_left;
			}
			else {
				sum += cur->_item + sst(cur->_left);
				cur = cur->_right;
			}
		}
		return sum;
	}
}



template <class T>
void BinarySearchTree<T>::_preOrderPrint(TreeNode<T>* node) {
	if (!node) return;
	cout << node->_item << "(" << node->_sst << ") ";
	_preOrderPrint(node->_left);
	_preOrderPrint(node->_right);
}

template <class T>
void BinarySearchTree<T>::preOrderPrint() {
	_preOrderPrint(_root);
	cout << endl;
}


template <class T>
void BinarySearchTree<T>::postOrderPrint() {
	_postOrderPrint(_root);
	cout << endl;
}



template <class T>
void BinarySearchTree<T>::_postOrderPrint(TreeNode<T>* node) {
	if (!node) return;
	_postOrderPrint(node->_left);
	_postOrderPrint(node->_right);
	cout << node->_item << "(" << node->_sst << ") ";
}

template <class T>
void BinarySearchTree<T>::inOrderPrint() {
	_inOrderPrint(_root);
	cout << endl;
}


template <class T>
void BinarySearchTree<T>::_inOrderPrint(TreeNode<T>* node) {
	if (!node) return;
	_inOrderPrint(node->_left);
	cout << node->_item << "(" << node->_sst << ") ";
	_inOrderPrint(node->_right);
}

template <class T>
void BinarySearchTree<T>::_printTree(int indent, TreeNode<T>* node, bool withSST) {

	if (!node)
		return;

	if (node->_right)
		_printTree(indent + 2, node->_right, withSST);
	for (int i = 0; i < indent; i++)
		cout << "  ";
	cout << node->_item;
	if (withSST)
		cout <<  "(s=" << node->_sst << ")";
	cout << endl;
	if (node->_left)
		_printTree(indent + 2, node->_left, withSST);


};


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



class MagicalPancakeGym {
private:
	BinarySearchTree<long long int> stack;
public:
	void addPancake(long long int weight);
	long long int minimalBottomPancake2Lift(long long int totalW);
	void printPancakes();
	long long int totalWeightAbovePancake(long long int w);
	MagicalPancakeGym() {}
};

long long int MagicalPancakeGym::totalWeightAbovePancake(long long int w)
{
	return stack.sumLE(w);
}

void MagicalPancakeGym::addPancake(long long int weight)
{
	stack.insert(weight);
}

void MagicalPancakeGym::printPancakes()
{
	stack.inOrderPrint();
}

long long int MagicalPancakeGym::minimalBottomPancake2Lift(long long int totalW)
{
	if (!totalW) {
		return 0;
	}
	else {
		if (!stack._root) {
			return -1;
		}
		else {
			TreeNode<long long int>* cur = stack._root;
			TreeNode<long long int>* best = new TreeNode<long long int>(-1);
			long long int sum = 0;
			while (cur) {
				if (cur->_left) {
					if (sum + cur->_item + cur->_left->_sst == totalW) {
						return cur->_item;
					}
					else if (sum + cur->_item + cur->_left->_sst < totalW) {
						if (cur->_right) {
							sum += cur->_left->_sst + cur->_item;
							cur = cur->_right;
						}
						else {
							return best->_item;
						}
					}
					else {
						best = cur;
						cur = cur->_left;
					}
				}
				else {
					if (sum + cur->_item == totalW) {
						return cur->_item;
					}
					else if (sum + cur->_item < totalW) {
						if (cur->_right) {
							sum += cur->_item;
							cur = cur->_right;
						}
						else {
							return best->_item;
						}
					}
					else {
						return cur->_item;
					}
				}
			}
			delete (best);
			return -1;
		}
	}
}

