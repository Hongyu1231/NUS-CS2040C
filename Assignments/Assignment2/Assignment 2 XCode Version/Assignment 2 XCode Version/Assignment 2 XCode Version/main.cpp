#include "linkedList.hpp"
#include <iostream>
#include <string>

using std::cout;
using std::endl;

void check(bool cond, const char* msg) {
    cout << (cond ? "[PASS] " : "[FAIL] ") << msg << endl;
}

int main() {
    cout << "===== LinkedList Edge Case Tests =====" << endl;

    // 1. 空链表
    List<int> a;
    check(a.empty(), "Empty list is empty()");
    check(a.size() == 0, "Empty list size=0");
    cout << "Empty list to_string(): " << a << endl;

    // 2. head/pop/extract_max 在空链表上应抛异常
    try { a.head(); check(false, "head() on empty should throw"); }
    catch (const std::out_of_range&) { check(true, "head() on empty throws"); }

    try { a.pop_head(); check(false, "pop_head() on empty should throw"); }
    catch (const std::out_of_range&) { check(true, "pop_head() on empty throws"); }

    try { a.extract_max(); check(false, "extract_max() on empty should throw"); }
    catch (const std::out_of_range&) { check(true, "extract_max() on empty throws"); }

    // 3. initializer_list 构造：单元素 & 多元素
    List<int> b{42};
    check(b.size() == 1 && b.head() == 42, "Initializer_list single element");

    List<int> c{1, 2, 3, 4};
    cout << "List c = " << c << endl;
    check(c.head() == 1, "head() returns first element");

    // 4. push_head + pop_head
    c.push_head(0);
    check(c.head() == 0, "push_head works");
    c.pop_head();
    check(c.head() == 1, "pop_head works");

    // 5. contains()
    check(c.contains(3), "contains(3) true");
    check(!c.contains(99), "contains(99) false");

    // 6. extract_max：最大值在头、中、尾
    List<int> d{10, 20, 30, 40};   // max at tail
    int max1 = d.extract_max();
    check(max1 == 40 && !d.contains(40), "extract_max tail works");

    d.push_head(50);               // max at head
    int max2 = d.extract_max();
    check(max2 == 50 && !d.contains(50), "extract_max head works");

    d.push_head(5); d.push_head(35); // max in middle
    int max3 = d.extract_max();
    check(max3 == 35 && !d.contains(35), "extract_max middle works");

    // 7. reverse：空链表、单节点、多节点
    List<int> e;
    e.reverse();
    check(e.empty(), "reverse empty list OK");

    List<int> f{99};
    f.reverse();
    check(f.head() == 99, "reverse single element OK");

    List<int> g{1, 2, 3};
    g.reverse();
    cout << "g reversed = " << g << endl;
    check(g.head() == 3, "reverse multi element OK");

    // 8. 拷贝构造 & 拷贝赋值（深拷贝测试）
    List<std::string> h{"apple", "banana"};
    List<std::string> i = h;    // copy ctor
    check(i.size() == h.size() && i.contains("banana"), "copy constructor works");

    List<std::string> j;
    j = h;                      // copy assignment
    check(j.size() == h.size() && j.contains("apple"), "copy assignment works");

    // 修改原始不影响拷贝
    h.pop_head();
    check(h.size() == 1 && j.size() == 2, "deep copy confirmed");

    // 9. 不同类型测试（bool/char/double）
    List<bool> k{true, false, true};
    cout << "List<bool> k = " << k << endl;

    List<char> l{'a', 'b', 'c'};
    cout << "List<char> l = " << l << endl;

    List<double> m{1.1, 2.2, 3.3};
    cout << "List<double> m = " << m << endl;

    cout << "===== All edge case tests done =====" << endl;
    return 0;
}
