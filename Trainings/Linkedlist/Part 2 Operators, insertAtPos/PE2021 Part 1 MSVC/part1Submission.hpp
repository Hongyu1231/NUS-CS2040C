#include <iostream>

using namespace std;

// if you use mac, just in case your code doesn't work, do this:
// sudo xcode-select --switch /Library/Developer/CommandLineTools/

template <class T>
T& List<T>::operator[](int idx) {
    if (idx >= _size) {
        std::cout << "Index out of bound error (operator[])" << endl;
        return _head->_item;
    }
    else {
        ListNode<T>* cur = _head;
        for (int i = 0; i < idx; i++) {
            cur = cur->_next;
        }
        return cur->_item;
    }
}
template <class T>
void List<T>::insertAtPos(int idx, T item) {
    if (idx > _size) {
        std::cout << "Index out of bound error (insertAtPos)" << endl;
    }
    else {
        ListNode<T>* cur = _head;
        if (!cur) {
            _head = new ListNode<T>(item);
        }
        else {
            if (!idx) {
                _head = new ListNode<T>(item);
                _head->_next = cur;
            }
            else if (idx == _size) {
                for (int i = 0; i < idx - 1; i++) {
                    cur = cur->_next;
                }
                cur->_next = new ListNode<T>(item);
            }
            else {
                for (int i = 0; i < idx - 1; i++) {
                    cur = cur->_next;
                }
                ListNode<T>* next = cur->_next;
                cur->_next = new ListNode<T>(item);
                cur->_next->_next = next;
            }
        }
        _size++;
    }
}

template <class T>
void List<T>::removeAtPos(int idx){
    if (idx >= _size) {
        std::cout << "Index out of bound error(removeAtPos)" << endl;
    }
    else {
        ListNode<T>* cur = _head;
        ListNode<T>* prev = _head;
        if (!cur) {
            return;
        }
        else {
            if (!idx) {
                ListNode<T>* temp = _head;
                _head = _head->_next;
                delete(temp);
                _size--;
            }
            else {
                for (int i = 0; i < idx; i++) {
                    prev = cur;
                    cur = cur->_next;
                }
                ListNode<T>* temp = cur;
                prev->_next = cur->_next;
                delete(temp);
                _size--;
            }
        }
    }

}
