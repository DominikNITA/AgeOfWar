#include <iostream>
#include "src/units/Archer.hpp"

int main() {
    std::cout << "Hello, World!" << std::endl;
    Archer archer;
    std::cout << archer.GetHp()<< std::endl;
    return 0;
}