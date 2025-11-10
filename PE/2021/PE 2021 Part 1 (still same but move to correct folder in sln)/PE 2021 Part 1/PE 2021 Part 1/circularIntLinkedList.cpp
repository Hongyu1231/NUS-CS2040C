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
	if (_size == 0 || _size == 1) {
		return;
	}
	else {
		_head = _head->_next;
	}
}

void CircularList::insertHead(int n)
{
	// modify this
	if (_size == 0) {
		_head = new ListNode(n);
		_head->_next = _head;
		_size++;
	}
	else if (_size == 1) {
		_head->_next = new ListNode(n);
		_head->_next->_next = _head;
		_size++;
	}
	else {
		ListNode* temp = _head->_next;
		_head->_next = new ListNode(n);
		_head->_next->_next = temp;
		_size++;

	}
};

void CircularList::removeHead()
{
	// modify this
	if (_size == 0) {
		return;
	}
	else if (_size == 1) {
		delete(_head);
		_head = NULL;
		_size--;
	}
	else {
		ListNode* temp = _head->_next;
		_head->_next = _head->_next->_next;
		delete(temp);
		_size--;
	}
}

void CircularList::print() {
	// modify this
	if (_size == 0) {
		std::cout << endl;
	}
	else {
		ListNode* cur = _head->_next;
		for (int i = 0; i < _size; i++) {
			std::cout << cur->_item << ' ';
			cur = cur->_next;
		}
		std::cout << endl;
	}
}

bool CircularList::exist(int n) {
	// modify this	
	ListNode* cur = _head;
	for (int i = 0; i < _size; i++) {
		if (cur->_item == n) {
			return true;
		}
		cur = cur->_next;
	}
	return false;
}

int CircularList::headItem()
{
	// modify this
	if (_size > 1) {
		return _head->_next->_item;
	}
	else {
		return _head->_item;
	}
}

CircularList::~CircularList()
{
	// modify this
	ListNode* cur = _head;
	for (int i = 0; i < _size; i++) {
		ListNode* temp = cur;
		cur = cur->_next;
		delete(temp);
	}
	_head = NULL;
	_size = 0;
};

