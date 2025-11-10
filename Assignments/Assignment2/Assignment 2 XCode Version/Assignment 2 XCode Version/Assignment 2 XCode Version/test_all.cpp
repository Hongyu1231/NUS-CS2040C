
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cassert>

#include "linkedlist.hpp"
#include "food.h"

// Tiny test helpers
#define CHECK(cond) do { if(!(cond)) { \
    std::cerr << "[FAIL] " << __FILE__ << ":" << __LINE__ << " -> " #cond << std::endl; return 1; } \
    else { std::cout << "[PASS] " << #cond << std::endl; } } while(0)

#define CHECK_EQ(a,b) do { auto _va=(a); auto _vb=(b); \
    if(!((_va)==(_vb))) { std::cerr << "[FAIL] " << __FILE__ << ":" << __LINE__ \
        << " -> " #a " == " #b << "  (lhs=" << _va << ", rhs=" << _vb << ")\n"; return 1; } \
    else { std::cout << "[PASS] " << #a " == " #b << std::endl; } } while(0)

int main() {
    std::cout << "===== FOOD TESTS =====\n";
    Food apple("Apple", 200);
    Food orange("Orange", 300);
    Food coffee("Coffee", 100);
    Food chicken("Chicken", 300);
    Food acai("Acai", 220);
    Food cake("Cake", 300);

    // operator+
    {
        auto mix = apple + orange;
        CHECK_EQ(mix.name(), std::string("Apple Orange"));
        CHECK_EQ((int)mix.calories(), 500);
    }

    // operator<
    {
        CHECK(apple < orange);
        CHECK(!(orange < apple));
        CHECK(!(chicken < cake)); // 300 !< 300
        CHECK(coffee < chicken);
    }

    // operator== (by calories)
    {
        CHECK(!(apple == orange));
        CHECK(chicken == cake);
        CHECK(!(acai == apple));
    }

    // operator<< formatting
    {
        std::ostringstream oss;
        oss << acai; // expected "Acai (220 kCal)"
        CHECK_EQ(oss.str(), std::string("Acai (220 kCal)"));
    }

    std::cout << "\n===== LIST<T> TESTS =====\n";

    // 1) default ctor + empty/size/to_string
    {
        List<int> a;
        CHECK(a.empty());
        CHECK_EQ(a.size(), (size_t)0);
        CHECK_EQ(a.to_string(), std::string("{}"));
    }

    // 2) initializer_list ctor + iteration + to_string
    {
        List<int> b{1,2,3};
        CHECK(!b.empty());
        CHECK_EQ(b.size(), (size_t)3);

        // range-for (iterator)
        std::vector<int> v;
        for (int x : b) v.push_back(x);
        CHECK_EQ(v.size(), (size_t)3);
        CHECK_EQ(v[0], 1); CHECK_EQ(v[1], 2); CHECK_EQ(v[2], 3);

        // const_iterator (cbegin/cend)
        const List<int>& bc = b;
        size_t count = 0; int sum = 0;
        for (auto it = bc.cbegin(); it != bc.cend(); ++it) { sum += *it; ++count; }
        CHECK_EQ(count, (size_t)3);
        CHECK_EQ(sum, 6);

        // to_string (expects "{1,2,3}" or similar)
        auto s = b.to_string();
        std::cout << "List<int> b = " << s << std::endl;
        CHECK(s.find("1") != std::string::npos && s.find("3") != std::string::npos);
    }

    // 3) push_head / pop_head / front semantics
    {
        List<std::string> c;
        c.push_head("world");
        c.push_head("hello");
        CHECK_EQ(c.size(), (size_t)2);
        CHECK_EQ(*(c.begin()), std::string("hello"));
        // pop_head() removes head; read element before popping
        auto it = c.begin();
        CHECK_EQ(*it, std::string("hello"));
        c.pop_head();
        CHECK_EQ(c.size(), (size_t)1);
        CHECK_EQ(*(c.begin()), std::string("world"));
        c.pop_head();
        CHECK(c.empty());
    }

    // 4) reverse
    {
        List<char> d{'a','b','c','d'};
        d.reverse();
        std::vector<char> v;
        for (auto ch : d) v.push_back(ch);
        CHECK_EQ(v[0],'d'); CHECK_EQ(v[1],'c'); CHECK_EQ(v[2],'b'); CHECK_EQ(v[3],'a');
    }

    // 5) contains
    {
        List<int> e{10,20,30};
        CHECK(e.contains(10));
        CHECK(e.contains(30));
        CHECK(!e.contains(40));
    }

    // 6) copy constructor
    {
        List<int> f{7,8,9};
        List<int> g = f;
        CHECK_EQ(g.to_string(), f.to_string());
        // mutate original; copy should remain same if deep copy
        // remove head element to mutate original
        f.pop_head();
        CHECK_EQ(g.size(), (size_t)3);
        CHECK_EQ(f.size(), (size_t)2);
    }

    // 7) assignment operator
    {
        List<std::string> h{"x","y"};
        List<std::string> i;
        i = h;
        CHECK_EQ(i.to_string(), h.to_string());
        h.pop_head();
        CHECK_EQ(i.size(), (size_t)2);
        CHECK_EQ(h.size(), (size_t)1);
    }

    // 8) extract_max (requires comparable type)
    {
        List<int> j{5,1,9,2,9,3};
        int mx = j.extract_max();
        CHECK_EQ(mx, 9);
        CHECK_EQ(j.size(), (size_t)5);
        // Extract again (there were two 9s)
        mx = j.extract_max();
        CHECK_EQ(mx, 9);
        CHECK_EQ(j.size(), (size_t)4);
    }

    // 9) different types (bool/char/double) basic smoke via to_string and iteration
    {
        List<bool> k{true,false,true};
        std::cout << "List<bool> k = " << k << std::endl; // relies on List<<

        List<char> l{'a','b','c'};
        std::ostringstream oss;
        oss << l;
        CHECK(oss.str().find('a') != std::string::npos);

        List<double> m{1.1,2.2,3.3};
        double sum = 0.0;
        for (auto x : m) sum += x;
        CHECK(sum > 6.5 && sum < 6.7);
    }

    std::cout << "===== ALL TESTS PASSED =====\n";
    return 0;
}
