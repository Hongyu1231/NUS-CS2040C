#include <iostream>
#include "circularIntLinkedList.h"
using namespace std;

ListNode::ListNode(int n)
{
	_item = n;
	_next = NULL;
}


////////////////////////////////////////////////////////////////////////////
//      You should ONLY modify the bodies of the following functions      //
// You should copy and paste ALL the functions below onto coursemology    //
////////////////////////////////////////////////////////////////////////////

void CircularList::advanceHead()
{
	// modify this
	if (_head) {
		_head = _head->_next;
	}
}

void CircularList::insertHead(int n)
{
	// modify this
	if (!_head) {
		_head = new ListNode(n);
		_head->_next = _head;
	}
	else {
		ListNode* temp = _head->_next;
		_head->_next = new ListNode(n);
		_head->_next->_next = temp;
	}
	_size++;
};

void CircularList::removeHead()
{
	// modify this
	if (_size > 1) {
		ListNode* temp = _head->_next;
		_head->_next = _head->_next->_next;
		delete(temp);
		_size--;
	}
	else if (_size == 1) {
		delete(_head);
		_size--;
		_head = NULL;
	}
}

void CircularList::print() {
	// modify this
	if (_size) {
		ListNode* cur = _head->_next;
		for (int i = 0; i < _size; i++) {
			cout << cur->_item << ' ';
			cur = cur->_next;
		}
	}
	cout << endl;
}

bool CircularList::exist(int n) {
	if (_size) {
		ListNode* cur = _head;
		for (int i = 0; i < _size; i++) {
			if (cur->_item == n) {
				return true;
			}
			cur = cur->_next;
		}
	}
	return false;
}

int CircularList::headItem()
{
	// modify this
	return _head->_next->_item;
}

CircularList::~CircularList()
{
	// modify this
	while (_head) {
		removeHead();
	}
};

