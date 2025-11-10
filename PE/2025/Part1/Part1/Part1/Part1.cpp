// CS2040C Assignment 1 Linked List.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include "LinkedList.h"
#include <cassert>

void reverse_test1();


int main()
{
    reverse_test1();

    // you should write more test cases for yourself
}

void reverse_test1()
{

    std::cout << "reverse_test1()" << std::endl;
    int vec[] = { 3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5, 8, 4, 3, 2, 1 };
    int vecSize = 16;

    List list;
    for (size_t idx = 0; idx < vecSize; idx++) {
        list.push_head(vec[idx]);
    }


    std::cout << "Original list" << std::endl;
    std::cout << list.to_string() << std::endl << std::endl;
    list.reverse_interval(1, 4);
    std::cout << "reverse_interval(1, 4)" << std::endl;
    std::cout << list.to_string() << std::endl << std::endl;
    std::cout << "reverse_interval(0, 3)" << std::endl;
    list.reverse_interval(0, 3);
    std::cout << list.to_string() << std::endl << std::endl;
    std::cout << "reverse_interval(10, 6)" << std::endl;
    list.reverse_interval(10, 6);
    std::cout << list.to_string() << std::endl << std::endl;
}
