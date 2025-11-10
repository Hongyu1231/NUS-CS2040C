#include "food.h"
#include <iostream>
#include "linkedlist.hpp"


List<Food> make_menu(){
    Food orange = Food("Orange", 300);
    Food apple = Food("Apple", 200);
    Food chicken = Food("Chicken", 300);
    Food coffee = Food("Coffee", 100);
    Food cake = Food("Cake", 300);
    Food acai = Food("Acai", 220);

    List<Food> menu;
    menu.push_head(orange);
    menu.push_head(apple);
    menu.push_head(chicken);
    menu.push_head(coffee);
    menu.push_head(cake);
    menu.push_head(acai);

    return menu;
}


// int main(){
//     auto menu = make_menu();
//     for (const auto& item : menu) {
//         std::cout << item << '\n' ;
//     };
// }
