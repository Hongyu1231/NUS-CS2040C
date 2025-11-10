#include "LinkedList.h"
#include <iostream>
// copy the following code to coursemology without the above line of "#include "LinkedList.h""

// Returns the value at head
int List::head() {
	return 0;
}

// Checks whether the container is empty
bool List::empty() const {
	return 0;
}

// Returns the number of elements
size_t List::size() const {
	return 0;
}

// Inserts an element to the head
void List::push_head(int element) {
	Node* node = new Node{ element, m_head };
	m_head = node;
	m_size++;
}

void List::reverse_interval(int a, int b) {
	// implement your code here.
		if (a == b) {
			return;
		}
		else if (a > b) {
			int temp = a;
			a = b;
			b = temp;
		}
			Node* cur = m_head;
			List lst;
			if (!a) {
				int temp;
				temp = pop_head();
				lst.push_head(temp);
				Node* last = lst.m_head;
				for (int i = 0; i < b; i++) {
					temp = pop_head();
					lst.push_head(temp);
				}
				Node* tempa = m_head;
				m_head = lst.m_head;
				last->next = tempa;
			}
			else {
				for (int i = 0; i < a - 1; i++) {
					cur = cur->next;
				}
				Node* temp = cur;
				int tem;
				cur = cur->next;
				Node* tempa = cur;
				tem = cur->element;
				lst.push_head(tem);
				cur = cur->next;
				delete(tempa);
				Node* last = lst.m_head;
				for (int i = 0; i < b - a; i++) {
					Node* tempa = cur;
					tem = cur->element;
					lst.push_head(tem);
					cur = cur->next;
					delete(tempa);
				}
				temp->next = lst.m_head;
				last->next = cur;
			}

}

void List::print() {
	Node* curr = m_head;
	for (int i = 0; i < m_size; i++)
	{
		std::cout << curr->element << " ";
		curr = curr->next;
	}
	std::cout << curr << " ";
	std::cout << std::endl;
}

// Removes the head element
int List::pop_head() {
	if (m_size == 1) {
		int temp = m_head->element;
		delete(m_head);
		m_head = nullptr;
		m_size--;
		return temp;
	}
	else {
		Node* temp = m_head;
		m_head = m_head->next;
		m_size--;
		int result = temp->element;
		delete(temp);
		return result;
	}
	
}

// Checks whether the container contains the specified element
bool List::contains(int element) const {

	return 0;
}

// Returns a std::string equivalent of the container
std::string List::to_string() const {
	std::string result;
	result += "{";
	std::string separator;
	for (Node* node = m_head; node != nullptr; node = node->next) {
		result += separator + std::to_string(node->element);
		separator = ", ";
	}
	result += "}";
	return result;
}
