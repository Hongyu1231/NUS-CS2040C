
#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <initializer_list>
#include <string>
#include <stdexcept>

template <typename T> struct Node {
  T element;
  Node<T> *next;

  Node(T element) : element{element}, next{nullptr} {}
  Node(T element, Node<T> *next) : element{element}, next{next} {}
};

template <typename T> class List {
private:
  size_t m_size;
  Node<T> *m_head;

  // Feel free to add helper functions here, if necessary
// ---- stringify helpers (put under `private:`) ----
static std::string elem_to_string(const std::string& s) {
    return std::string("\"") + s + "\"";
}

static std::string elem_to_string(const char* s) {
    return s ? (std::string("\"") + s + "\"") : std::string("\"\""); 
}
static std::string elem_to_string(char* s) {
    return s ? (std::string("\"") + s + "\"") : std::string("\"\"");
}

static std::string elem_to_string(char c) {
    return std::string("'") + c + "'";
}

static std::string elem_to_string(bool b) {
    return b ? "true" : "false";
}

static std::string elem_to_string(short x) { return std::to_string(static_cast<long long>(x)); }
static std::string elem_to_string(int x) { return std::to_string(x); }
static std::string elem_to_string(long x) { return std::to_string(x); }
static std::string elem_to_string(long long x) { return std::to_string(x); }

static std::string elem_to_string(unsigned short x) { return std::to_string(static_cast<unsigned long long>(x)); }
static std::string elem_to_string(unsigned int x) { return std::to_string(x); }
static std::string elem_to_string(unsigned long x) { return std::to_string(x); }
static std::string elem_to_string(unsigned long long x) { return std::to_string(x); }

static std::string elem_to_string(float x) { return std::to_string(static_cast<double>(x)); }
static std::string elem_to_string(double x) { return std::to_string(x); }
static std::string elem_to_string(long double x) { return std::to_string(static_cast<double>(x)); }

template <typename U>
static std::string elem_to_string(const U&) {
    static_assert(sizeof(U) == 0, "elem_to_string is not defined for this T; ""add an overload for your type.");
    return {};
}


public:
  class iterator{
    private:
      Node<T> *cur;
    public:
      explicit iterator(Node<T> *p = nullptr) : cur(p) {}
      T &operator*() const { return cur->element; }
      T *operator->() const { return &cur->element; }
      iterator& operator++() { cur = cur->next;
        return *this;
      }
      bool operator!=(const iterator &rhs) { return cur != rhs.cur; }
  };

  class const_iterator{
    private:
      const Node<T> *cur;
    public:
      explicit const_iterator(Node<T> *p = nullptr) : cur(p) {}
      const T &operator*() const { return cur->element; }
      const T *operator->() const { return &cur->element; }
      const_iterator& operator++() { cur = cur->next;
        return *this;
      }
      bool operator!=(const const_iterator &rhs) { return cur != rhs.cur; }
  };

  iterator begin() { return iterator(m_head); }
  iterator end()   { return iterator(nullptr); }

// begin/end for const objects
  const_iterator begin() const { return const_iterator(m_head); }
  const_iterator end()   const { return const_iterator(nullptr); }

// also provide explicit cbegin/cend
  const_iterator cbegin() const { return const_iterator(m_head); }
  const_iterator cend()   const { return const_iterator(nullptr); }

      // Constructs an empty container
      List() : m_size{0}, m_head{nullptr}
      {
      }

  // Constructs the container with the contents of the initializer list
  List(std::initializer_list<T> init_list) : m_size{0}, m_head{nullptr} {
    auto it = init_list.end();
    while (--it != init_list.begin()) {
      push_head(*it);
    }
    push_head(*it);
  }

  // Rule of three:
  // If a class requires a user-defined destructor, a user-defined copy
  // constructor, or a user-defined copy assignment operator, it almost
  // certainly requires all three.

  // Destructor
  ~List() {
    // TODO: (Optional) Implement this method
    while (m_head){
      Node<T> *temp = m_head;
      m_head = m_head->next;
      delete temp;
    }
    m_size = 0;
  }

    //Copy constructor
    List(const List<T> &other) : m_size(0), m_head{nullptr}
    {
      // TODO: (Optional) Implement this method
      if (other.m_size == 0){
        return;
      }else{
          m_size = other.m_size;
          Node<T> *cur_src = other.m_head->next;
          m_head = new Node<T>(other.m_head->element);
          Node<T> *copy_cur = m_head;
          while (cur_src)
          {
            copy_cur->next = new Node<T>(cur_src->element);
            copy_cur = copy_cur->next;
            cur_src = cur_src->next;
          }
        }
    }

  // Copy assignment
  List<T> &operator=(const List<T> &other) {
    // TODO: (Optional) Implement this method
    if (this == &other) return *this; 

    while (m_head) {
        Node<T>* tmp = m_head;
        m_head = m_head->next;
        delete tmp;
    }
    m_size = 0;

    if (other.m_size == 0)
    {
      return *this;
    }else{
          m_size = other.m_size;
          Node<T> *cur_src = other.m_head->next;
          m_head = new Node<T>(other.m_head->element);
          Node<T> *copy_cur = m_head;
          while (cur_src)
          {
            copy_cur->next = new Node<T>(cur_src->element);
            copy_cur = copy_cur->next;
            cur_src = cur_src->next;
          }
          return *this;
        }
  }

    // Returns the contents of the head node
    const T &head()
    {
      if (m_size <= 0)
      {
        throw std::out_of_range("List is empty");
      }
      return m_head->element;
    }

  // Checks whether the container is empty
  bool empty() const { return m_size == 0; }

  // Returns the number of elements
  size_t size() const { return m_size; }

  // Inserts an element to the head
  void push_head(const T& element) {
    Node<T> *node = new Node<T>{element, m_head};
    m_head = node;
    m_size++;
  }

  // Removes the head element
  void pop_head() {
    if (m_size <= 0) {
      throw std::out_of_range("List is empty");
    }
    Node<T> *node = m_head;
    m_head = m_head->next;
    delete node;
    m_size--;
  }

  // Checks whether the container contains the specified element
  bool contains(const T& element) const {
    // TODO: Implement this method
    const Node<T> *current = m_head;
    while (current){
      if (current->element == element){
        return true;
      }
      current = current->next;
    }
    return false;
  }

  // Extracts the maximum element from the container
  T extract_max() {
    // TODO: Implement this method
    if (m_size == 0) {
      throw std::out_of_range("List is empty");
    }else{
      Node<T> *prev = nullptr;
      Node<T> *cur = m_head;
      Node<T> *max_node = m_head;
      Node<T> *max_prev = nullptr;

      while (cur){
        if (max_node->element < cur->element){
          max_node = cur;
          max_prev = prev;
        }
        prev = cur;
        cur = cur->next;
      }

      if (max_prev){
        max_prev->next = max_node->next;
      }else{
        m_head = max_node->next;
      }

      T max = max_node->element;
      delete max_node;
      m_size--;
      return max;
    }
  }

  // Reverse the container
  void reverse() {
    // TODO: Implement this method
    if (m_size == 0 || m_size ==1){
      return;
    }
    Node<T> *prev = nullptr;
    Node<T> *cur = m_head;
    while (cur)
    {
      Node<T> *temp = cur->next;
      cur->next = prev;
      prev = cur;
      cur = temp;
    }
    m_head = prev;
  }

  // Returns a std::string equivalent of the container
  std::string to_string() const {
    // TODO: Implement this method
    if (m_size == 0){
    return "{}";
    }
    else{
      const Node<T> *current = m_head;
      std::string my_string = "{";
      bool first = true;
      while (current)
      {
        if (!first){
          my_string += ", ";
        }
        std::string single = elem_to_string(current->element);
        my_string += single;
        current = current->next;
        first = false;
      }
      my_string += "}";
      return my_string;
    }
  }

};

template <typename T>
std::ostream& operator<<(std::ostream& os, const List<T>& other) {
  os << other.to_string();
  return os;
}

#endif
