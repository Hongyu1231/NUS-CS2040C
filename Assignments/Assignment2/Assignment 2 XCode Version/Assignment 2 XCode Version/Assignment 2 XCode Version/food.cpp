#include "food.h"
#include <iostream>
#include <vector>// allowed, but we won't instantiate List<vector<...>> to avoid elem_to_string issues

using namespace std;
using std::cout;
using std::endl;

Food Food:: operator+(const Food& rhs) const
{
    // modify this function
    std::string name = m_name + " " + rhs.m_name;
    float calories = m_calories + rhs.m_calories;
    return Food(name, calories);
}


bool Food:: operator<(const Food& rhs) const
{
    if(m_calories < rhs.m_calories){
        return true;
    }else{
        return false;
    }
}

bool Food:: operator==(const Food& rhs) const
{
    if (m_calories == rhs.m_calories){
        return true;
    }else{
        return false;
    }
}

std::ostream& operator<<(std::ostream& os, const Food& rhs) {
    os << rhs.name() << " (" << rhs.calories() << " kCal" << ")";
    return os;
}

void check(bool cond, const char* msg) {
    cout << (cond ? "[PASS] " : "[FAIL] ") << msg << endl;
}

// int main(){
//     Food orange = Food("Orange", 300);
//     Food apple = Food("Apple", 200);
//     Food chicken = Food("Chicken", 300);
//     Food coffee = Food("Coffee", 100);
//     Food cake = Food("Cake", 300);
//     Food acai = Food("Acai", 220);

//     cout << "Testing for +" << endl;
//     Food food1 = orange + apple;
//     check(food1.name() == "Orange Apple", "Name : Orange Apple");
//     check(food1.calories() == 500, "Calories : 500");

//     Food food2 = chicken + coffee;
//     check(food2.name() == "Chicken Coffee", "Name : Chicken Coffee");
//     check(food2.calories() == 400, "Calories : 400");

//     Food food3 = cake + acai;
//     check(food3.name() == "Cake Acai", "Name : Cake Acai");
//     check(food3.calories() == 520, "Calories : 520");

//     cout << "Testing for <" << endl;
//     check((orange < apple) == false, "Orange is bigger than Apple");

//     check((chicken < coffee) == false, "chicken is bigger than coffee");

//     check((acai < cake) == true, "acai is smaller than cake");

//     cout << "Testing for ==" << endl;
//     check((orange == apple) == false, "Orange is not equal to Apple");

//     check((chicken == orange) == true, "chicken is equal to orange");

//     check((acai == cake) == false, "acai is not equal to cake");

//     cout << "Testing for <<" << endl;
//     cout << acai << endl;
//     cout << cake << endl;

//     cout << "\nAll tests completed.\n";
//     return 0;

// }
