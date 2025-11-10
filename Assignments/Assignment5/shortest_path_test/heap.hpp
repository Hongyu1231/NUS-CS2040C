#pragma once
#include <math.h>

#include <iostream>
using namespace std;

#ifndef HEAPHPP
#define HEAPHPP

#define DEFAULTHEAPSIZE 1023

template <class T>
class Heap {
 protected:
  T* _heap;
  int _size;

  int parent(int i) const { return (i - 1) / 2;}
  int left(int i) const { return 2 * i + 1; }
  int right(int i) const { return 2 * i + 2; }

  void incrementSize() {
      _size++;
  }

  void decrementSize() {
      _size--;
  }

  void bubbleUp(int index) {
      while (index > 0) {
          int p = parent(index);
          if (_heap[index] > _heap[p]) {
              swap(_heap[index], _heap[p]);
          }
          else {
              break;
          }
          index = p;
      }
  }

  void bubbleDown(int index) {
      while (left(index) < _size) {
          int leftIndex = left(index);
          int rightIndex = right(index);
          if (rightIndex < _size) {
              if (_heap[rightIndex] > _heap[leftIndex]) {
                  if (_heap[rightIndex] > _heap[index]) {
                      swap(_heap[index], _heap[rightIndex]);
                      index = rightIndex;
                  }
                  else {
                      break;
                  }
              }
              else {
                  if (_heap[leftIndex] > _heap[index]) {
                      swap(_heap[index], _heap[leftIndex]);
                      index = leftIndex;
                  }
                  else {
                      break;
                  }
              }
          }
          else {
              if (_heap[leftIndex] > _heap[index]) {
                  swap(_heap[index], _heap[leftIndex]);
                  index = leftIndex;
              }
              else {
                  break;
              }
          }
      }
  }

  int findItem(const T& item) const {
      if (empty()) throw std::out_of_range("Empty heap!");
      int index = 0;
      while (index < _size && _heap[index] != item) {
          ++index;
      }
      if (index == _size) throw std::out_of_range("Item is not in the heap!");
      return index;
  }


  

 public:
     Heap() {
         _heap = new T[DEFAULTHEAPSIZE];
         _size = 0;
     }

  int size() const {
    // TODO: implement this
    return _size;
  }

  bool empty() const {
    // TODO: implement this
    return (_size == 0);

  }
  void insert(const T&);
  T extractMax();
  T peekMax() const;
  void printHeapArray() const;
  void printTree() const;
  void changeKey(const T& from, const T& to);
  void deleteItem(const T&);

  ~Heap() { delete[] _heap; };
};

template <class T>
void Heap<T>::insert(const T& item) {
  // TODO: implement this
    int Size = size();
    if (Size >= DEFAULTHEAPSIZE) {
        throw std::out_of_range("The heap is full");
    }
    _heap[Size] = item;
    incrementSize();
    bubbleUp(Size);
}

template <class T>
T Heap<T>::extractMax() {
  // TODO: implement this
    if (empty()) {
        throw std::out_of_range("The heap is empty");
    }
    else {
        int Size = size();
        T temp = _heap[0];
        _heap[0] = _heap[Size - 1];
        decrementSize();
        if (!empty()) { bubbleDown(0); }
        return temp;
    }
}

template <class T>
T Heap<T>::peekMax() const {
  // TODO: What happens if the heap is empty?
    if (empty()) {
        throw std::out_of_range("The heap is empty");
    }
    else {
        return _heap[0];
    }
};

template <class T>
void Heap<T>::printHeapArray() const {
  for (int i = 0; i < size(); i++) {
    cout << _heap[i] << " ";
  }
  cout << endl;
}

template <class T>
void Heap<T>::changeKey(const T& from, const T& to) {
  // TODO: implement this
    if (from > to) {
        int index = findItem(from);
        _heap[index] = to;
        bubbleDown(index);
    }
    else if (from < to) {
        int index = findItem(from);
        _heap[index] = to;
        bubbleUp(index);
    }
}

template <class T>
void Heap<T>::deleteItem(const T& x) {
  // TODO: implement this
    int index = findItem(x);
    int Size = size();
    _heap[index] = _heap[Size - 1];
    decrementSize();
    Size--;
    if (index < Size) {
        if ((_heap[index] > _heap[parent(index)]) && (index > 0)) {
            bubbleUp(index);
        }
        else {
            bubbleDown(index);
        }
    }
}

template <class T>
void Heap<T>::printTree() const {
  int parity = 0;
  if (size() == 0) return;
  int space = pow(2, 1 + (int)log2f(size())), i;
  int nLevel = (int)log2f(size()) + 1;
  int index = 0, endIndex;
  int tempIndex;

  for (int l = 0; l < nLevel; l++) {
    index = 1;
    parity = 0;
    for (i = 0; i < l; i++) index *= 2;
    endIndex = index * 2 - 1;
    index--;
    tempIndex = index;
    while (index < size() && index < endIndex) {
      for (i = 0; i < space - 1; i++) cout << " ";
      if (index == 0)
        cout << "|";
      else if (parity)
        cout << "\\";
      else
        cout << "/";
      parity = !parity;
      for (i = 0; i < space; i++) cout << " ";
      index++;
    }
    cout << endl;
    index = tempIndex;
    while (index < size() && index < endIndex) {
      for (i = 0; i < (space - 1 - ((int)log10(_heap[index]))); i++)
        cout << " ";
      cout << _heap[index];
      for (i = 0; i < space; i++) cout << " ";
      index++;
    }

    cout << endl;
    space /= 2;
  }
}

#endif
