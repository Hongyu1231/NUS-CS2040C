// Part3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <algorithm>
#include <vector>

/*
===================================================================================================

// Please submit the code in this section only

===================================================================================================
*/


class AmoebaGladiatorGame {
public:

    AmoebaGladiatorGame(int* powers, int size) : _powers(powers), p_size(size) {}

    int minRemainingPower();

private:
    int* _powers;   
    int p_size;     
};


int AmoebaGladiatorGame::minRemainingPower() {
    // implement your code here
    int sum = 0;
    std::vector<int> powers(_powers, _powers + p_size);
    std::sort(powers.begin(), powers.end());
    if (p_size % 2 == 0) {
        for (int i = 1; i < p_size; i += 2) {
            sum += powers[i];
        }
    }
    else {
        for (int i = 0; i < p_size; i += 2) {
            sum += powers[i];
        }
    }
    return sum;
}


/*
===================================================================================================

// Do not submit the code in this section

===================================================================================================
*/

int main()
{
    int vec[] = { 2499, 2399, 1899, 2099, 1120};
    int vecSize = 5;
    AmoebaGladiatorGame agg(vec, vecSize); 
    std::cout << "{";
    for (int i=0;i<5;i++)
        std::cout << vec[i] << (i==4?"}":",");
    std::cout << " gives a minimal remaining total power of " << agg.minRemainingPower() << std::endl; // should be 5718

    int vec2[] = { 76,23,42,11,42,11 };
    AmoebaGladiatorGame agg2(vec2, 6);
    std::cout << "{";
    for (int i = 0; i < 6; i++)
        std::cout << vec2[i] << (i == 5 ? "}" : ",");
    std::cout << " gives a minimal remaining total power of " << agg2.minRemainingPower() << std::endl; // should be 129

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
