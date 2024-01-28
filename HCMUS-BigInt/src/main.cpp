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
    std::string numberA = "3097116595406184932388856750610341727241735002883812299195854974";
    std::string numberB = "-7951438622797642347864531501667508524220392144227540361428532707";
    BigInt a = numberA;
    BigInt b = numberB;
    
    std::cout << a << std::endl;
    std::cout << b << std::endl;
    // std::cout << 10 % 3 << std::endl;
    std::cout << a + b << std::endl;
    return 0;
}
