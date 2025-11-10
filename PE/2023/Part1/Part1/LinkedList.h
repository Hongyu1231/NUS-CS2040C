

#include <iostream>
using namespace std;

#define SPLITSTR "Splitting: "
#define INTOSTR "Into :"
#define MERGESTR "Merging: "


class ListNode {

private:
    int _item;
    ListNode* _next;

public:
    ListNode( int );        // Constructs the list node with parameter
    void printItem();       // Prints the item

    friend class List;
};

class List {

private:
    ListNode* _head;
    int _size;

public:
    List();                             // Constructs an empty list
    ~List();                            // Destructs a list

    void insertHead( int );             // Inserts the new value into the linked list
    int getHeadItem();                  // Retrieves the value in the head node
    int removeHead();                   // Removes the head node and returns the value removed

    void bubbleSort();            // TODO: Implement bubble sort
    void mergeSort();                   // Calls the recursive merge sort function

    void split( List* );                // TODO: Splits the linked lists into two halves
    void merge( List* );                // TODO: Merge two linked lists in ascending order

    void print();                 // Prints all items of the linked lists.
};








/*
 * LISTNODE CONSTRUCTUORS AND FUNCTIONS
 */
ListNode::ListNode(int item) {
    _item = item;
    _next = NULL;
}

void ListNode::printItem() {
    cout << _item;
}


/*
 * LIST CONSTRUCTORS AND FUNCTIONS
 */
List::List() {
    _head = NULL;
    _size = 0;
}

List::~List() {
    while (_head) {
        removeHead();
    }
}

void List::insertHead(int item) {
    ListNode* newNode = new ListNode(item);
    newNode->_next = _head;
    _head = newNode;
    _size++;
}

int List::getHeadItem() {
    return _head->_item;
}

int List::removeHead() {
    int item = -32768;  
    ListNode* temp;

    if (_head) {
        temp = _head;
        item = getHeadItem();
        _head = _head->_next;
        delete temp;
        _size--;
    }

    return item;
}

void List::bubbleSort() {

    // TODO: Implement bubble sort on this implementation of single linked list.
    //       Print the linked list after every pass in the outer iteration
    //       using print(false) function in List class if parameter is true.
    //       The list should be sorted in ascending order.

    // ENTER YOUR ANSWER BELOW.
    if (_size == 0 || _size == 1) {
        print();
    }
    else {
        for (int i = 0; i < _size - 1; i++) {
            if (_head->_item > _head->_next->_item) {
                ListNode* temp = _head;
                _head = _head->_next;
                temp->_next = _head->_next;
                _head->_next = temp;
            }
            ListNode* cur = _head->_next;
            ListNode* parent = _head;
            while (cur->_next) {
                if (cur->_item > cur->_next->_item) {
                    parent->_next = cur->_next;
                    cur->_next = cur->_next->_next;
                    parent->_next->_next = cur;
                    parent = parent->_next;
                }
                else {
                    parent = cur;
                    cur = cur->_next;
                }
            }
            print();
        }
    }

    // ENTER YOUR ANSWER ABOVE.
}

void List::mergeSort() {
    if (_size == 1) {
        return;
    }
    else {
        // modify this function
        // each time you split a list
        cout << SPLITSTR;
        // original unsplitted list print
        print();
        cout << INTOSTR << endl;
        // original splitted list print (but it's halved)
        // the other splitted list print
        List* otherList = new List();
        split(otherList);
        print();
        otherList->print();
        mergeSort();
        otherList->mergeSort();
        // after you sorted the two lists
        cout << MERGESTR << endl;
        // original splitted list print (but it's halved)
        // the other splitted list print
        print();
        otherList->print();
        // after you merged the above two sorted lists
        cout << INTOSTR;
        // print the merged sorted single list
        merge(otherList);
        print();
    }

}


void List::split(List* otherList) {
    // TODO: Implement splitting of the current list.
    //       The first half of the list will be pointed by itself.
    //       The second half of the list will be pointed by otherList.
    //       It is guaranteed that the original list will have more than one node.
    //
    //       No need to print within split()
    
    // ENTER YOUR ANSWER BELOW.
    int Size = _size / 2;
    ListNode* cur = _head;
    for (int i = 0; i < Size - 1; i++) {
        cur = cur->_next;
    }

    ListNode* start = cur->_next;
    cur->_next = NULL;
    otherList->_head = start;
    otherList->_size = _size - Size;
    _size = Size;
   // ENTER YOUR ANSWER ABOVE.
}

void List::merge(List* otherList) {
    // TODO: Implement merging of current list and otherList.
    //       The otherList should be empty after merging.
    //       It is guaranteed that both lists are non-empty.
    //
    //       No need to print within merge()
    // ENTER YOUR ANSWER BELOW.
    List result;
    ListNode* cur1 = _head;
    ListNode* cur2 = otherList->_head;
    while (_head && otherList->_head) {
        if (cur1->_item > cur2->_item) {
            result.insertHead(cur2->_item);
            otherList->removeHead();
            cur2 = otherList->_head;
        }
        else {
            result.insertHead(cur1->_item);
            removeHead();
            cur1 = _head;
        }
    }
    if (!_head && !otherList->_head) {
        while (result._head) {
            insertHead(result._head->_item);
            result.removeHead();
        }
    }
    else if (!_head && otherList->_head) {
        while (otherList->_head) {
            insertHead(otherList->_head->_item);
            otherList->removeHead();
        }
        while (result._head) {
            insertHead(result._head->_item);
            result.removeHead();
        }
    }
    else if (_head && !otherList->_head) {
        while (result._head) {
            insertHead(result._head->_item);
            result.removeHead();
        }
    }

    // ENTER YOUR ANSWER ABOVE.
}

void List::print() {

    ListNode* curr = _head;

    while (curr) {
        cout << curr->_item;
        cout << " ";
        curr = curr->_next;
    }

    cout << endl;
}




