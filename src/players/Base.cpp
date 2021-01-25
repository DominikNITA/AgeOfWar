//
// Created by Dominik on 12/28/2020.
//

#include "Base.hpp"
#include <iostream>

Base::Base() {
    m_hp = 100;
}

void Base::draw() {
    std::cout << m_hp << std::endl;
}
