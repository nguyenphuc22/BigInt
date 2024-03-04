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
    // // Testing the BigInt class
    // std::string numberA = "-1234567899999999999999999999999999999999999999";
    // std::string numberB = "987654321";

    // std::string numberA = "-23";
    // std::string numberB = "-8";

    // std::string numberA = "25";
    // std::string numberB = "5";

    std::string numberA = "-321951297601675515252227491198117788783175472632709509415199737";
    std::string numberB = "-7125621409543227992459498260887594782257886371717132382511361239";

    // std::string numberA = "-5935220000933903639816775045754345534007128532925586632547301727";
    // std::string numberB = "898532864482628945552150500173137729286786857788216556983970900";

    BigInt a = numberA;
    BigInt b = numberB;
    
    std::cout << a << std::endl;
    std::cout << b << std::endl;
    
    std::cout << 10 % 3 << std::endl;

    // std::cout << a + b << std::endl;
    // std::cout << a - b << std::endl;
    std::cout << a * b << std::endl;
    std::cout << a / b << std::endl;
    std::cout << a % b << std::endl;  // -321951297601675515252227491198117788783175472632709509415199737
    // std::cout << a % b << std::endl;  // 3050108643148725305735375454418792195279658324862629924436669173

    return 0;
}

