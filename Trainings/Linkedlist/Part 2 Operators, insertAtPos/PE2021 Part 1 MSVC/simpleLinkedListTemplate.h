#pragma once
using namespace std;

template <class T>
class List;

template <class T>
class ListNode
{
private:
	T _item;
	ListNode<T> *_next;

public:
	ListNode(T);
	T content() { return _item; };
	void print() { cout << _item; };
	friend class List<T>;
};

template <class T>
class List
{
private:
	int _size;
	ListNode<T> *_head;

public:

	// for the following functions, you cannot assume that the list is not empty or empty...
	List()	{	_size = 0;	_head = NULL;};

	~List();
	void insertHead(T);
	void print(); // print the items in one single row if false, otherwise, print each item in a new line
	int size() { return _size; };
	bool empty() { return _size == 0; };

	// .. except for the following functions, we can assume that the list is not empty when you call them.
	T headItem();
	void removeHead();

    T& operator [](int idx);
    void insertAtPos(int idx,T item);
    void removeAtPos(int idx);

};

#include "simpleLinkedListTemplate.hpp"
