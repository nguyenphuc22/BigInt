//
//  BigInt.cpp
//  BigInt
//
//  Created by Phuc Nguyen on 19/01/2024.
//

#include "BigInt.hpp"

// Hàm từ số nguyên sang dạng biểu diễn BigInt
std::vector<int> BigInt::from_integer(long long value) {
    std::vector<int> result;
    while (value) {
        result.push_back(value % base);
        value /= base;
    }
    if (result.empty()) {
        result.push_back(0);
    }
    return result;
}

// Constructor
BigInt::BigInt(long long value) {
    sign = (value >= 0) ? 1 : -1;
    blocks = from_integer(std::abs(value));
}

// Toán tử cộng
BigInt BigInt::operator+(const BigInt& other) const {
    // Triển khai phép cộng tại đây
    return BigInt();  // Kết quả tạm thời
}

// Toán tử trừ
BigInt BigInt::operator-(const BigInt& other) const {
    // Triển khai phép trừ tại đây
    return BigInt();  // Kết quả tạm thời
}

// Toán tử nhân
BigInt BigInt::operator*(const BigInt& other) const {
    // Triển khai phép nhân tại đây
    return BigInt();  // Kết quả tạm thời
}

// Toán tử chia
BigInt BigInt::operator/(const BigInt& other) const {
    // Triển khai phép chia tại đây
    return BigInt();  // Kết quả tạm thời
}

// Toán tử chia lấy dư
BigInt BigInt::operator%(const BigInt& other) const {
    // Triển khai phép chia lấy dư tại đây
    return BigInt();  // Kết quả tạm thời
}

// Phương thức lũy thừa
BigInt BigInt::pow(const BigInt& exponent, const BigInt& modulus) const {
    // Triển khai phương thức lũy thừa tại đây
    return BigInt();  // Kết quả tạm thời
}

// Ghi dữ liệu ra ostream
std::ostream& operator<<(std::ostream& os, const BigInt& bigint) {
    os << "BigInt: ";
    for (long i = bigint.blocks.size() - 1; i >= 0; i--) {
        os << bigint.blocks[i];
        if (i > 0) {
            os << " ";
        }
    }
    return os;
}

// Các phương thức trợ giúp khác có thể được thêm vào tại đây
