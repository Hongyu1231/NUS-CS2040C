#pragma once


/////////////////////////////////////////////////////////////////
//
//        You should not modify any of these
//
/////////////////////////////////////////////////////////////////
class ListNode
{
private:
	int _item;
	ListNode *_next;

public:
	ListNode(int);
	friend class CircularList;
};

class CircularList
{
private:
	int _size;
	ListNode *_head;

public:
	CircularList()
	{
		_size = 0;
		_head = NULL;
	};

	int headItem();
	void insertHead(int);
	void removeHead();
	void print();
	bool exist(int);
	void advanceHead();
	~CircularList();

};