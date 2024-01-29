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
    std::string numberA = "-2477404291473547985834945730711921637000289069882267980120313093";
    std::string numberB = "-7556364152863011662189543349809444438703697225023640607802209567";
    BigInt a = numberA;
    BigInt b = numberB;
    std::cout << a << std::endl;
    std::cout << b << std::endl;
    //std::cout << 10 % 3 << std::endl;
    std::cout << a + b << std::endl;
    

    
    return 0;
}
