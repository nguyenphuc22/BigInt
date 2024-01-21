//
//  main.cpp
//  HelloWorld
//
//  Created by Phuc Nguyen on 18/01/2024.
//

#include <iostream>
#include <vector>
#include "../include/BigInt.hpp"
#include "../src/BigInt.cpp"
#include <string>
#include <fstream>



int main() {
    // Testing the BigInt class
    
    // Read input from file CreateTestCaseBigInt/data/add.txt
    std::ifstream inputFile("/CreateTestCaseBigInt/data/add.txt");
    if (!inputFile) {
        std::cerr << "Unable to open file";
        return 1; // return with error code 1
    }

    std::string line;
    while (std::getline(inputFile, line)) {
        // process the line
        std::cout << line << std::endl;
    }

    inputFile.close();


    return 0;
}


    