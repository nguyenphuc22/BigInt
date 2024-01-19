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

class BigInt {
private:
    int base = 1000000;
    int sign = 1;  // Positive by default
    std::vector<int> blocks;

    std::vector<int> from_integer(long long value);

public:
    BigInt(long long value = 0);

    BigInt operator+(const BigInt& other) const;
    BigInt operator-(const BigInt& other) const;
    BigInt operator*(const BigInt& other) const;
    BigInt operator/(const BigInt& other) const;
    BigInt operator%(const BigInt& other) const;

    BigInt pow(const BigInt& exponent, const BigInt& modulus) const;

    friend std::ostream& operator<<(std::ostream& os, const BigInt& bigint);
    
    // Có thể thêm các phương thức trợ giúp khác nếu cần
};

#endif /* BigInt_hpp */
