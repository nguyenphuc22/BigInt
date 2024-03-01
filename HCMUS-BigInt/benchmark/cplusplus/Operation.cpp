//
// Created by Phuc Nguyen on 06/02/2024.
//

#include <string>
#include <sstream>
#include "../../src/BigInt.cpp"

class Operation {
public:

    int order;
    BigInt firstNumber;
    int operation;
    BigInt secondNumber;
    BigInt result;

    Operation() {
        order = 0;
        firstNumber = BigInt("0");
        operation = 0;
        secondNumber = BigInt("0");
        result = BigInt("0");
    }

    void parse(const std::string& line) {
        std::istringstream iss(line);
        std::string temp;

        std::getline(iss, temp, ',');
        order = std::stoi(temp);

        std::getline(iss, temp, ',');
        firstNumber = BigInt(temp);

        std::getline(iss, temp, ',');
        operation = std::stoi(temp);

        std::getline(iss, temp, ',');
        secondNumber = BigInt(temp);

        std::getline(iss, temp, ',');
        result = BigInt(temp);
    }

    int getOrder() const {
        return order;
    }

    const BigInt &getFirstNumber() const {
        return firstNumber;
    }

    std::string getOperation() const {
        switch (operation) {
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

    const BigInt &getSecondNumber() const {
        return secondNumber;
    }

    const BigInt &getResult() const {
        return result;
    }

    BigInt execute() const {
        switch (operation) {
            case 1:
                return firstNumber + secondNumber;
            case 2:
                return firstNumber - secondNumber;
            case 3:
                return firstNumber * secondNumber;
            case 4:
                return firstNumber / secondNumber;
            case 5:
                return firstNumber % secondNumber;
            case 6:
                return firstNumber ^ secondNumber;
            default:
                return BigInt("0");
        }
    }
};