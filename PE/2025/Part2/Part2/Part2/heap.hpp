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

 public:
  Heap(int size, T* vec, bool printStep = true);

  int size() const {
      return _size;
  }
  void printHeapArray() const;
  void printTree() const;
  ~Heap() { delete[] _heap; };

  void swap(int a, int b, T* vec) {
      T temp = vec[a];
      vec[a] = vec[b];
      vec[b] = temp;
  }
 };

template <class T>
Heap<T>::Heap(int size, T* vec, bool printStep ) {

    // implement your code here
    int n;
    _heap = new T[DEFAULTHEAPSIZE];
    for (int j = 0; j < size; j++) {
        _heap[j] = vec[j];
    }
    _size = size;
    for (int i = size-1; i >=0 ; i--)
    {
        n = i;
        while (2*n + 1 <= _size - 1) {
            if (2 * n + 1 == _size - 1) {
                if (_heap[n] >= _heap[2 * n + 1]) {
                    swap(n, 2 * n + 1, _heap);
                    n = 2 * n + 1;
                }
                else {
                    break;
                }
            }
            else if (2 * n + 1 < _size - 1) {
                if (_heap[2 * n + 1] >= _heap[2 * n + 2]) {
                    if (_heap[2 * n + 2] <= _heap[n]) {
                        swap(n, 2 * n + 2, _heap);
                        n = 2 * n + 2;
                    }
                    else { break; }
                }
                else {
                    if (_heap[2 * n + 1] <= _heap[n]) {
                        swap(n, 2 * n + 1, _heap);
                        n = 2 * n + 1;
                    }
                    else {
                        break;
                    }
                }
            }
        }
        if (printStep)
            printHeapArray();
    }
}


template <class T>
void Heap<T>::printHeapArray() const {

  // Do NOT modify this function
  for (int i = 0; i < size(); i++) {
    cout << _heap[i] << " ";
  }
  cout << endl;
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
