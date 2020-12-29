//
// Created by Dominik on 12/28/2020.
//

#include "Base.hpp"
#include <iostream>

Base::Base() {
    _hp = 100;
}

void Base::Draw() {
    std::cout << _hp << std::endl;
}
