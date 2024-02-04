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
    std::string numberA = "-419237164716282338679912076450847286372489822800563360086940738";
    std::string numberB = "-5487485363702421039844700230210910494150929862503459821040897191";
    BigInt a = numberA;
    BigInt b = numberB;
    std::cout << a << std::endl;
    std::cout << b << std::endl;
    //std::cout << 10 % 3 << std::endl;
    std::cout << (a * b).to_string() << std::endl;

    
    return 0;
}
