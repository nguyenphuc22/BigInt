//
//  BigInt.cpp
//  BigInt
//
//  Created by Phuc Nguyen on 19/01/2024.
//

#include "../include/BigInt.hpp"

// Hàm từ chuỗi sang dạng biểu diễn BigInt
std::vector<int> BigInt::from_string(const std::string& inputString) {
    
    std::vector<int> result;

    if (inputString.empty()) {
        result.push_back(0);
        return result;
    }


    int startIndex = (inputString[0] == '-') ? 1 : 0;

    int block = 0;
    int multiplier = 1;
    for (long i = inputString.length() - 1; i >= startIndex; i--) {
        char digit = inputString[i];
        if (isdigit(digit)) {
            block += (digit - '0') * multiplier;
            multiplier *= 10;
            if (multiplier >= base) {
                result.push_back(block);
                block = 0;
                multiplier = 1;
            }
        } else {
            throw std::invalid_argument("Invalid character in input string.");
        }
    }

    if (block > 0) {
        result.push_back(block);
    }

    if (result.empty()) {
        result.push_back(0);
    }

    return result;
}


// Constructor
BigInt::BigInt(const std::string& inputString) {
        if (inputString.empty()) {
            // Xử lý lỗi hoặc đặt mặc định 0
            sign = 0;
            return;
        }

        // Xác định dấu dựa trên ký tự đầu tiên của chuỗi
        if (inputString[0] == '-') {
            sign = -1;
        } else {
            sign = 1;
        }

        // Chuyển đổi chuỗi thành khối số nguyên (blocks)
        blocks = from_string(inputString);}

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
    if (bigint.sign == -1) {
        os << "-";
    }
    for (long i = bigint.blocks.size() - 1; i >= 0; i--) {
        os << bigint.blocks[i];
        if (i > 0) {
            os << " ";
        }
    }
    return os;
}

// Các phương thức trợ giúp khác có thể được thêm vào tại đây
