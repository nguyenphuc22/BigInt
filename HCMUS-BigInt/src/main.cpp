//
//  main.cpp
//  HelloWorld
//
//  Created by Phuc Nguyen on 18/01/2024.
//

#include <iostream>
#include <vector>
#include "../include/BigInt.hpp"
#include "BigInt.cpp"
#include <string>




int main() {
    // Testing the BigInt class
    std::string numberA = "-1418998903515976507539400518208058259135237535743543270508057629";
    std::string numberB = "4579204161657841338512583747584587177837977337470489792455487420";
    BigInt a = numberA;
    BigInt b = numberB;
    std::cout << a << std::endl;
    std::cout << b << std::endl;
    // std::cout << 10 % 3 << std::endl;
    std::cout << a + b << std::endl;
    return 0;
}
