//
//  BigInt.hpp
//  BigInt
//
//  Created by Phuc Nguyen on 19/01/2024.
//

#ifndef BigInt_hpp
#define BigInt_hpp

#include <iostream>
#include <vector>
#include <cmath>
#include <string>

class BigInt {
private:

    int base; // Quy ước chia chuỗi string thành các block, mỗi block 6 chữ số. Default = 1000000
    int sign;  // Số dương lớn hơn 1, Số âm bé hơn 1, Số 0 = 0. Default = 0
    std::vector<int> blocks;

    std::vector<int> from_string(const std::string& inputString = "0");

    // Có thể thêm các phương thức trợ giúp khác nếu cần
    bool isFirstLargerThanSecond(const BigInt& a, const BigInt& b) const;
    bool isGreaterOrEqual(const BigInt& other) const;
    void removeLeadingZeros();
    BigInt addSameSignNumbers(const BigInt& other) const;
    BigInt addDifferentSignNumbers(const BigInt& other) const;
    BigInt subtractDifferentSignNumbers(const BigInt& other) const;
    BigInt subtractSameSignNumbers(const BigInt& other) const;
    BigInt multiplySameBasicAlgorithm(const BigInt& other) const;
    BigInt divideSameBasicAlgorithm(const BigInt& other) const;
    

public:
    BigInt(const std::string& inputString = "0");

    BigInt operator+(const BigInt& other) const;
    BigInt operator-(const BigInt& other) const;
    BigInt operator*(const BigInt& other) const;
    BigInt operator/(const BigInt& other) const;
    BigInt operator%(const BigInt& other) const;
    bool operator==(const BigInt& other) const;
    bool operator!=(const BigInt& other) const;
    bool operator<(const BigInt& other) const;
    bool operator>(const BigInt& other) const;
    bool operator<=(const BigInt& other) const;
    bool operator>=(const BigInt& other) const;

    BigInt pow(const BigInt& power) const;

    std::string to_string() const;

    friend std::ostream& operator<<(std::ostream& os, const BigInt& bigint);
    
    // Static function declaration
    static BigInt abs(const BigInt& num);

};
#endif /* BigInt_hpp */



