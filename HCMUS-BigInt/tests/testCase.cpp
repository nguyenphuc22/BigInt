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
#include <sstream>

std::string cal(BigInt a, BigInt b, int op) {
    switch (op)
    {
    case 1:
        return (a + b).to_string();
    case 2:
        return (a - b).to_string();
    case 3:
        return (a * b).to_string();
    case 4:
        return (a / b).to_string();
    case 5:
        return (a % b).to_string();
    case 6:
        return (a.pow(b)).to_string();
    default:
        return "0";
    }
}

std::string getSymbol(int op) {
    switch (op)
    {
    case 1:
        return "+";
    case 2:
        return "-";
    case 3:
        return "*";
    case 4:
        return "/";
    case 5:
        return "%";
    case 6:
        return "^";
    default:
        return "0";
    }
}   

int main(int argc, char* argv[]) {
    // Get path from parameter
    // Path Example ../../CreateTestCaseBigInt/data/add.txt
    std::string path = argv[1];
    std::cerr << "Path: " << path << std::endl;

    // Read input from file CreateTestCaseBigInt/data/add.txt
    std::ifstream inputFile(path);
    if (!inputFile) {
        std::cerr << "Unable to open file";
        return 1; // return with error code 1
    }

    std::string line;
    
    while (std::getline(inputFile, line)) {
        // process the line
        std::cerr << line << std::endl;

        std::string delimiter = ",";
        std::istringstream iss(line);
        std::string token;
        int stt = 0;
        int op = 0;
        BigInt a,b,result;
        int count = 0;
        while (std::getline(iss, token, ',')) {
            count++;
            switch (count)
            {
            case 1:
                stt = std::stoi(token);
                break;
            case 2:
                a = BigInt(token);
                break;
            case 3:
                op = std::stoi(token);
                break;    
            case 4:
                b = BigInt(token);
                break;
            case 5:
                result = BigInt(token);
                break;
            default:
                break;
            }

        }

        std::cerr << "stt: " << stt << std::endl;
        std::cerr << a.to_string() << " " << getSymbol(op) << " " << b.to_string() << std::endl;
        std::cerr << "Result: " << result.to_string() << std::endl; 
        std::string yourRes = cal(a,b,op);
        std::cerr << "Your Result: " << yourRes << std::endl; 

        if (yourRes == result.to_string())
        {
            std::cerr << "Correct" << std::endl;
        } else {
            std::cerr << "Incorrect" << std::endl;
            inputFile.close();
            return 1;
        }
               
    }

    inputFile.close();


    return 0;
}



    