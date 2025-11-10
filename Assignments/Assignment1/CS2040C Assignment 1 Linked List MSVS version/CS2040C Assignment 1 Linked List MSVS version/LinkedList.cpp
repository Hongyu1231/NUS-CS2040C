#include "LinkedList.h"

// copy the following code to coursemology without the above line of "#include "LinkedList.h""
#include <stdexcept>
// Returns the value at head
int List::head() {
	if (m_head == nullptr){
		throw std::out_of_range("There is no head");
	}
	return m_head->element;
}

// Checks whether the container is empty
bool List::empty() const {
	return m_size == 0;
}

// Returns the number of elements
size_t List::size() const {
	return m_size;
}

// Inserts an element to the head
void List::push_head(int element) {
	m_head = new Node(element, m_head);
	m_size++;
}

// Removes the head element
int List::pop_head() {
	if (m_head == nullptr){
		throw std::out_of_range("There is no head");
	}
	Node *old = m_head;
	m_head = old->next;
	m_size--;
	int value = old->element;
	delete old;
	return value;
}

// Checks whether the container contains the specified element
bool List::contains(int element) const {
	Node *carriage = m_head;
	while (carriage){
		if (carriage->element == element){
			return true;
		}
		carriage = carriage->next;
	}
	return false;
}

// Returns a std::string equivalent of the container
std::string List::to_string() const {
	if (m_size == 0){
		std::string mystring = "{}";
		return mystring;
	}
	Node *carriage = m_head;
	std::string mystring = "{";
	for (size_t i = 0; i < m_size; i++){
		mystring += std::to_string(carriage->element);
		mystring += ", ";
		carriage = carriage->next;
	}
	mystring.pop_back();
	mystring.pop_back();
	mystring += "}";
	return mystring;
}
