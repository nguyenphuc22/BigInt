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
    std::string numberA = "-1234567899999999999999999999999999999999999999";
    std::string numberB = "987654321";
    BigInt a = numberA;
    BigInt b = numberB;
    
    std::cout << a << std::endl;
    std::cout << b << std::endl;
    
    return 0;
}
