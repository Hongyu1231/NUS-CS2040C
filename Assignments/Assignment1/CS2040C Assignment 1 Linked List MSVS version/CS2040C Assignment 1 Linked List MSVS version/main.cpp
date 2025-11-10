// CS2040C Assignment 1 Linked List.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include "LinkedList.h"
#include <cassert>

void push_head_test1();
void pop_head_test1();
void pop_head_test2();

int main()
{
    push_head_test1();
    pop_head_test1();
    pop_head_test2();


    // you should write more test cases for yourself
}

void push_head_test1()
{

    std::cout << "push_head_test1()" << std::endl;
    int vec[] = { 3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5, 8, 9, 7, 9, 3 };
    int vecSize = 16;

    List list;
    for (size_t idx = 0; idx < vecSize; idx++) {
        list.push_head(vec[idx]);
    }

    std::cout << list.to_string() << std::endl;
    /* Should print out:
    {3, 9, 7, 9, 8, 5, 3, 5, 6, 2, 9, 5, 1, 4, 1, 3}
    */
}

void pop_head_test1()
{
    std::cout << "pop_head_test1()" << std::endl;
    int vec[] = { 3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5, 8, 9, 7, 9, 3 };
    int vecSize = 16;

    List list;
    for (size_t idx = 0; idx < vecSize; idx++) {
        list.push_head(vec[idx]);
    }

    for (size_t idx = 0; idx < vecSize/2; idx++) { // only pop half of the list
        list.pop_head();
    }
    std::cout << list.to_string() << std::endl;
    /* Should print out:
    {6, 2, 9, 5, 1, 4, 1, 3}
    */
}

void pop_head_test2()
{
    std::cout << "pop_head_test2()" << std::endl;
    int vec[] = {1};
    int vecSize = 1;

    List list;
    for (size_t idx = 0; idx < vecSize; idx++) {
        list.push_head(vec[idx]);
    }

    for (size_t idx = 0; idx < vecSize; idx++) { // only pop half of the list
        list.pop_head();
    }
    std::cout << list.to_string() << std::endl;
   
}
