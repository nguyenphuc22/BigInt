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
    std::string numberA = "3759508939468945290690602781261427382545278405367953156731973648";
    std::string numberB = "-781374637790191719826613278031318188586397245784086790117031401";
    BigInt a = numberA;
    BigInt b = numberB;
    std::cout << a << std::endl;
    std::cout << b << std::endl;
    //std::cout << 10 % 3 << std::endl;
    std::cout << a + b << std::endl;

    
    return 0;
}
