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
    std::string numberA = "-9845960901611477327337980562165193039812369949679182253041139040";
    std::string numberB = "-8401875673030729449764225190365828558579533708397501016284947981";
    BigInt a = numberA;
    BigInt b = numberB;
    std::cout << a << std::endl;
    std::cout << b << std::endl;
    //std::cout << 10 % 3 << std::endl;
    std::cout << a + b << std::endl;

    
    return 0;
}
