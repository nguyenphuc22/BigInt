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
    std::string numberA = "5587016961521737837404991158695554760981639996058431558634581740";
    std::string numberB = "5944200336649355900868929377426282289486978551705342380702676518";
    BigInt a = numberA;
    BigInt b = numberB;
    std::cout << a << std::endl;
    std::cout << b << std::endl;

    std::cout << (a % b).to_string() << std::endl;

    return 0;
}
