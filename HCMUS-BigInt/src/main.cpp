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
    std::string numberA = "2991279206630463745487196709939029235081480309238617453245920030";
    std::string numberB = "-263389197212022517218648564415930210446200383848871239872029511";
    BigInt a = numberA;
    BigInt b = numberB;
    
    std::cout << a << std::endl;
    std::cout << b << std::endl;
    // std::cout << 10 % 3 << std::endl;
    std::cout << a + b << std::endl;
    return 0;
}
