#pragma once
#ifndef TREE_H
#define TREE_H

#include <algorithm>
#include <cassert>
#include <functional>
#include <string>

using std::string;

template <typename T>
std::string my_to_string(const T& t) {
    return std::to_string(t);
}

template <>
std::string my_to_string(const std::string& t) {
    return "\"" + t + "\"";
}

template <typename T> struct Node {
    T element;
    int height;
    Node<T>* left;
    Node<T>* right;

    Node(T element)
        : element{ element }, height{ 0 }, left{ nullptr }, right{ nullptr } {
    }
    Node(T element, int height)
        : element{ element }, height{ height }, left{ nullptr }, right{ nullptr } {
    }
};

template <typename T> class Tree {
private:
    size_t m_size;
    Node<T>* m_root;

public:
    // Constructor
    Tree();

    // Rule of three:
    // If a class requires a user-defined destructor, a user-defined copy
    // constructor, or a user-defined copy assignment operator, it almost
    // certainly requires all three.

    // Destructor
    ~Tree();

    Tree(const Tree& other);
    Tree<T>& operator=(const Tree<T>& other);

    // Returns a pointer to the root
    Node<T>* root();

    // Checks whether the tree is empty
    bool empty() const;

    // Returns the number of elements
    size_t size() const;

    // Returns the height of the tree
    int height() const;

    // Inserts the specified element
    void insert(T element);

    // Checks whether the container contains the specified element
    bool contains(T element) const;

    // Returns the maximum element
    T max() const;

    // Returns the minimum element
    T min() const;

    // Returns the successor of the specified element
    T successor(T element);

    // Convert each element in the tree to string in pre-order.
    string pre_order();

    // Convert each element in the tree to string in order.
    string in_order();

    // Convert each element in the tree to string in post-order.
    string post_order();

    // Returns a string equivalent of the tree
    string to_string(bool with_height = true) const {
        return m_to_string(with_height, m_root, 0);
    }

private:
    string m_to_string(bool with_height, Node<T>* node, int ident) const {
        string res;
        if (node == nullptr) {
            return res;
        }
        if (node->right != nullptr) {
            res += m_to_string(with_height, node->right, ident + 2);
        }
        for (int i = 0; i < ident; i++) {
            res += " ";
        }
        res += my_to_string(node->element);
        if (with_height) {
            res += "(h=" + my_to_string(node->height) + ")";
        }
        res += "\n";
        if (node->left != nullptr) {
            res += m_to_string(with_height, node->left, ident + 2);
        }
        return res;
    }

    // Feel free to declare helper functions here, if necessary
    int get_height(Node<T>* node) const;

    bool is_balanced(Node<T>* Node) const;

    bool is_left_heavy(Node<T>* Node) const;

    bool is_right_heavy(Node<T>* Node) const;

    Node<T>* is_parent(Node<T>* node) const;

    void update_height(Node<T>* node) const;

    void right_rotate(Node<T>* node);

    void left_rotate(Node<T>* node);

    void balance_tree(T element);

    void destroy(Node<T>* node);

    void revise_height(Node<T>* node);

    Node<T>* clone(Node<T>* node);

};

// Constructor
template <typename T> Tree<T>::Tree() {
    m_root = nullptr;
    m_size = 0;
    // TODO: Implement this method
}

// Destructor
template <typename T> Tree<T>::~Tree() {
    // TODO: Implement this method
    destroy(m_root);
    m_root = nullptr;
    m_size = 0;
}

// Returns a pointer to the root
template <typename T> Node<T>* Tree<T>::root() {
    // TODO: Implement this method
    return m_root;
}

// Checks whether the tree is empty
template <typename T> bool Tree<T>::empty() const {
    // TODO: Implement this method
    return m_size == 0;
}

// Returns the number of elements
template <typename T> size_t Tree<T>::size() const {
    // TODO: Implement this method
    return m_size;
}

// Returns the height of the tree
template <typename T> int Tree<T>::height() const {
    // TODO: Implement this method
    if (empty()) {
        return -1;
    }
    return m_root->height;
}

// Inserts an element
template <typename T> void Tree<T>::insert(T element) {
    // TODO: Implement this method
    if (empty()) {
        m_root = new Node<T>(element, 0);
        m_size++;
    }
    else {
        Node<T>* node = m_root;
        Node<T>* parent = nullptr;
        while (node) {
            parent = node;
            if (node->element < element) {
                node = node->right;
            }
            else if (node->element > element) {
                node = node->left;
            }
            else {
                return;
            }
        }

        Node<T>* child;
        if (parent->element < element) {
            parent->right = new Node<T>(element, 0);
            child = parent->right;
        }
        else {
            parent->left = new Node<T>(element, 0);
            child = parent->left;
        }

        revise_height(parent);
        balance_tree(element);
        m_size++;
    }
}

// Checks whether the container contains the specified element
template <typename T> bool Tree<T>::contains(T element) const {
    // TODO: Implement this method
    Node<T>* cur = m_root;
    while (cur) {
        if (cur->element > element) {
            cur = cur->left;
        }
        else if (cur->element < element) {
            cur = cur->right;
        }
        else {
            return true;
        }
    }
    return false;
}

// Returns the maximum element
template <typename T> T Tree<T>::max() const {
    // TODO: Implement this method
    if (empty()) {
        throw std::runtime_error("It is an empty tree!");
    }
    else {
        Node<T>* right_child = m_root;
        while (right_child->right) {
            right_child = right_child->right;
        }
        return right_child->element;
    }
}

// Returns the minimum element
template <typename T> T Tree<T>::min() const {
    // TODO: Implement this method
    if (empty()) {
        throw std::runtime_error("It is an empty tree!");
    }
    else {
        Node<T>* left_child = m_root;
        while (left_child->left) {
            left_child = left_child->left;
        }
        return left_child->element;
    }
}

// Returns the successor of the specified element
template <typename T> T Tree<T>::successor(T element) {
    // TODO: Implement this method
    if (empty()) {
        throw std::runtime_error("Empty tree!");
    }
    else {
        Node<T>* cur = m_root;
        Node<T>* succ = nullptr;

        while (cur) {
            if (cur->element > element) {
                succ = cur;
                cur = cur->left;
            }
            else {
                cur = cur->right;
            }
        }
        if (!succ) {
            throw std::out_of_range("No successor found!");
        }
        return succ->element;
    }
}

template <typename T>
string _pre_order(Node<T>* node) {
    return my_to_string(node->element)
        + (node->left == nullptr ? "" : " " + _pre_order(node->left))
        + (node->right == nullptr ? "" : " " + _pre_order(node->right));
}

template <typename T>
string Tree<T>::pre_order() {
    if (m_root == nullptr) {
        return "";
    }
    return _pre_order(m_root);
}

template <typename T>
string _in_order(Node<T>* node) {
    return (node->left == nullptr ? "" : _in_order(node->left) + " ")
        + my_to_string(node->element)
        + (node->right == nullptr ? "" : " " + _in_order(node->right));
}

template <typename T>
string Tree<T>::in_order() {
    // TODO: Implement this method
    if (m_root == nullptr) {
        return "";
    }
    return _in_order(m_root);
}

template <typename T>
string _post_order(Node<T>* node) {
    return (node->left == nullptr ? "" : _post_order(node->left) + " ")
        + (node->right == nullptr ? "" : _post_order(node->right) + " ")
        + my_to_string(node->element);
}

template <typename T>
string Tree<T>::post_order() {
    // TODO: Implement this method
    if (m_root == nullptr) {
        return "";
    }
    return _post_order(m_root);
}

template <typename T> int Tree<T>::get_height(Node<T>* Node) const {
    if (!Node) {
        return -1;
    }
    else {
        return Node->height;
    }
}

template <typename T> bool Tree<T>::is_balanced(Node<T>* node) const {
    if (!node) {
        return true;
    }
    int diff = get_height(node->left) - get_height(node->right);
    if (diff > 1 || diff < -1) {
        return false;
    }
    else {
        return true;
    }

}

template <typename T> bool Tree<T>::is_left_heavy(Node<T>* Node) const {
    if (!Node) {
        return false;
    }
    if (get_height(Node->left) > get_height(Node->right)) {
        return true;
    }
    return false;
}

template <typename T> bool Tree<T>::is_right_heavy(Node<T>* Node) const {
    if (!Node) {
        return false;
    }
    if (get_height(Node->left) < get_height(Node->right)) {
        return true;
    }
    return false;
}

template <typename T> Node<T>* Tree<T>::is_parent(Node<T>* node) const {
    Node<T>* parent = nullptr;
    Node<T>* cur = m_root;
    while (cur != node) {
        if (cur->element > node->element) {
            parent = cur;
            cur = cur->left;
        }
        else if (cur->element < node->element) {
            parent = cur;
            cur = cur->right;
        }
        else {
            break;
        }
    }
    return parent;
}

template <typename T> void Tree<T>::update_height(Node<T>* node) const {
    if (!node) return;
    node->height = std::max(get_height(node->left), get_height(node->right)) + 1;
}


template <typename T> void Tree<T>::left_rotate(Node<T>* node) {
    if (!node->right) {
        throw std::logic_error("Left rotation requires a right child!");
    }
    else {
        if (node == m_root) {
            Node<T>* parent = m_root->right;
            m_root->right = parent->left;
            parent->left = m_root;
            update_height(m_root);
            m_root = parent;
            update_height(m_root);
        }
        else {
            Node<T>* parent = node->right;
            node->right = parent->left;
            Node<T>* grandparent = is_parent(node);
            parent->left = node;
            if (grandparent) {
                if (grandparent->left == node) {
                    grandparent->left = parent;
                }
                else {
                    grandparent->right = parent;
                }
            }
            update_height(node);
            update_height(parent);
            revise_height(is_parent(parent));
        }

    }
}

template <typename T> void Tree<T>::right_rotate(Node<T>* node) {
    if (!node->left) {
        throw std::logic_error("Right rotation requires a left child!");
    }
    else {
        if (node == m_root) {
            Node<T>* parent = m_root->left;
            m_root->left = parent->right;
            parent->right = m_root;
            update_height(m_root);
            m_root = parent;
            update_height(m_root);
        }
        else {
            Node<T>* parent = node->left;
            node->left = parent->right;
            Node<T>* grandparent = is_parent(node);
            parent->right = node;
            if (grandparent) {
                if (grandparent->left == node) {
                    grandparent->left = parent;
                }
                else {
                    grandparent->right = parent;
                }
            }
            update_height(node);
            update_height(parent);
            revise_height(is_parent(parent));
        }
    }
}

template <typename T> void Tree<T>::balance_tree(T element) {
    if (empty()) return;
    else {
        Node<T>* node = m_root;
        Node<T>* inbalance = nullptr;
        while (node) {
            if (!is_balanced(node)) {
                inbalance = node;
            }
            if (node->element < element) {
                node = node->right;
            }
            else if (node->element > element) {
                node = node->left;
            }
            else {
                break;
            }
        }

        if (!inbalance) {
            return;
        }
        if (is_left_heavy(inbalance)) {
            if (is_right_heavy(inbalance->left)) {
                left_rotate(inbalance->left);
            }
            right_rotate(inbalance);
        }
        else if (is_right_heavy(inbalance)) {
            if (is_left_heavy(inbalance->right)) {
                right_rotate(inbalance->right);
            }
            left_rotate(inbalance);
        }
    }
}

template <typename T> void Tree<T>::destroy(Node<T>* node) {
    if (!node) { return; }
    destroy(node->left);
    destroy(node->right);
    delete node;
}

template <typename T> void Tree<T>::revise_height(Node<T>* node) {
    while (node) {
        int height = node->height;
        update_height(node);
        int updated_height = node->height;
        if (height == updated_height) {
            break;
        }
        node = is_parent(node);
    }
}

template <typename T> Tree<T>& Tree<T>::operator=(const Tree<T>& other) {
    if (this == &other) {
        return *this;
    }

    destroy(m_root);
    m_size = 0;
    m_root = nullptr;

    m_size = other.m_size;
    m_root = clone(other.m_root);

    return *this;
}

template <typename T> Node<T>* Tree<T>::clone(Node<T>* node) {
    if (!node) return nullptr;

    Node<T>* new_node = new Node<T>(node->element, node->height);
    new_node->left = clone(node->left);
    new_node->right = clone(node->right);
    return new_node;
}

template <typename T> Tree<T>::Tree(const Tree<T>& other) : m_size(other.m_size), m_root(nullptr) {
    m_root = clone(other.m_root);
}


#endif
