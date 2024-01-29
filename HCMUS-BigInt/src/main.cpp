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
    std::string numberA = "-7421903176996987557369991703289173744964500542688475416066551206";
    std::string numberB = "0";
    BigInt a = numberA;
    BigInt b = numberB;
    std::cout << a << std::endl;
    std::cout << b << std::endl;
    //std::cout << 10 % 3 << std::endl;
    std::cout << a - b << std::endl;

    
    return 0;
}
