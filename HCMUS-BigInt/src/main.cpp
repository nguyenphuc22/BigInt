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
    std::string numberA = "-883284780222250187602246943385468613731179259113868211670157257";
    std::string numberB = "7825677861431383937643704415119235773467021777086931606702754645";
    BigInt a = numberA;
    BigInt b = numberB;
    std::cout << a << std::endl;
    std::cout << b << std::endl;

    std::cout << (a / b).to_string() << std::endl;

    return 0;
}
