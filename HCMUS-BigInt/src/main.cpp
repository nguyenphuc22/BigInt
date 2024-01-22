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
    std::string numberA = "-668222339512204605446038134115500570468692621770824816858158573";
    std::string numberB = "-4450419050808833222129587873117464101993807907124669069093473099";
    BigInt a = numberA;
    BigInt b = numberB;
    
    std::cout << a << std::endl;
    std::cout << b << std::endl;
    
    // std::cout << 10 % 3 << std::endl;
    std::cout << a + b << std::endl;

    return 0;
}
