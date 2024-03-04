// BigInt_add_sub_mul.hpp

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
#include <cmath>
#include <iomanip>
using namespace std;

class BigInt {
private:

    int base; // Quy ước chia chuỗi string thành các block, mỗi block 6 chữ số. Default = 1000000
    int sign;  // Số dương lớn hơn bằng 1, Số âm bé hơn 1, Số 0 = 0. Default = 0
    vector<int> blocks;

    // vector<int> from_string(const string& inputString = "0");
    vector<int> from_string(const string& inputString);

    // void normalize();
    void removeLeadingZeros();
    bool isFirstLargerThanSecond(const BigInt& a, const BigInt& b) const;
    bool isZero() const;
    BigInt& setSign(int newSign);
    BigInt negate() const;
    BigInt subtractNumbers(const BigInt& larger, const BigInt& smaller) const;
    BigInt subtractWithSign(const BigInt& other) const;

    // Additional helper methods for multiplication
    bool isSmall() const;
    BigInt getHighPart(size_t m2) const;
    BigInt getLowPart(size_t m2) const;
    BigInt shiftLeft(size_t m) const;
    BigInt simpleMultiply(const BigInt& a, const BigInt& b) const;
    BigInt karatsubaMultiply(const BigInt& x, const BigInt& y) const;

    BigInt(const std::vector<int>& blocks, int sign) : blocks(blocks), sign(sign) {
        // You might want to call removeLeadingZeros() here to clean up any leading zeros
        removeLeadingZeros();
    }

    // Additional helper methods for dividation
    void shiftRight(int shiftBy);
    void removeLeadingZeros4divice();

    // // Additional helper methods for modulus
    bool isLessThan(const BigInt& other) const;
    // BigInt abs() const;

    //
    BigInt multiplySameBasicAlgorithm(const BigInt& other) const;
    BigInt divideSameBasicAlgorithm(const BigInt& other) const;

public:
    BigInt(const string& inputString = "0");

    BigInt operator-() const;
    BigInt operator*(int rhs) const {
        // Convert int to BigInt and call existing BigInt to BigInt multiplication
        return *this * BigInt(std::to_string(rhs));
    }

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

    string to_string() const;

    friend ostream& operator<<(ostream& os, const BigInt& bigint);


    // // Static member function to return the absolute value of a BigInt
    // static BigInt abs(const BigInt& num) {
    //     BigInt result = num; // Make a copy of num
    //     result.sign = (result.sign != 0) ? 1 : 0; // Make the sign positive unless num is 0
    //     return result;
    // }

    // Static function declaration
    static BigInt abs(const BigInt& num);

    // BigInt& operator+=(const BigInt& other);

};
#endif /* BigInt_hpp */



