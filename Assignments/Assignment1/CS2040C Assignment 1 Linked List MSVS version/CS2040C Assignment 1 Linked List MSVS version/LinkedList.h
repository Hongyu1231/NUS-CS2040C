#pragma once
#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <initializer_list>
#include <string>

struct Node {
    int element;
    Node* next;

    Node(int element) : element{ element }, next{ nullptr } {}
    Node(int element, Node* next) : element{ element }, next{ next } {}
};

class List {
private:
    size_t m_size;
    Node* m_head;

public:
    // Constructs an empty container
    List() : m_size{ 0 }, m_head{ nullptr } {}

    // Constructs the container with the contents of the initializer list
    List(std::initializer_list<int> init_list) : m_size{ 0 }, m_head{ nullptr } {
        auto it = init_list.end();
        while (--it != init_list.begin()) {
            push_head(*it);
        }
        push_head(*it);
    }

    // Returns the value at head
    int head();

    // Checks whether the container is empty
    bool empty() const;

    // Returns the number of elements
    size_t size() const;

    // Inserts an element to the head
    void push_head(int element);

    // Removes the head element and returns its value
    int pop_head();

    // Checks whether the container contains the specified element
    bool contains(int element) const;

    // Converts the container to std::string
    std::string to_string() const;
};

#endif