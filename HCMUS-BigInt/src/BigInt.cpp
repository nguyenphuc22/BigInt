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

void BigInt::removeLeadingZeros() {
    while (blocks.size() > 1 && blocks.back() == 0) {
        blocks.pop_back();
    }
}

void BigInt::normalize() {
    for (size_t i = 0; i < blocks.size() - 1; ++i) {
        int carry = blocks[i] / base;
        blocks[i] %= base;
        blocks[i + 1] += carry;
    }

    removeLeadingZeros();
}




// // Constructor
// BigInt::BigInt(const std::string& inputString) {
//         base = 1000000;  // 10^6
        
//         if (inputString.empty()) {
//             // Xử lý lỗi hoặc đặt mặc định 0
//             sign = 0;
//             return;
//         }

//         // Xác định dấu dựa trên ký tự đầu tiên của chuỗi
//         if (inputString[0] == '-') {
//             sign = -1;
//         } else {
//             sign = 1;
//         }

//         // Chuyển đổi chuỗi thành khối số nguyên (blocks)
//         blocks = from_string(inputString);
// }


BigInt::BigInt(const std::string& inputString) {
    base = 1000000; // 10^6

    if (inputString.empty()) {
        sign = 0;
        return;
    }

    sign = (inputString[0] == '-') ? -1 : 1;
    blocks = from_string(inputString);
    normalize();
}


// // Toán tử cộng
// BigInt BigInt::operator+(const BigInt& other) const {
//     // Triển khai phép cộng tại đây
//     return BigInt();  // Kết quả tạm thời
// }


BigInt BigInt::operator+(const BigInt& other) const {
    if (blocks.empty() || other.blocks.empty()) {
        return BigInt("0");
    }

    if (sign != other.sign) {
        return handleDifferentSignsSubtraction(other);
    }

    BigInt result;
    result.sign = sign;
    int carry = 0;
    size_t n = std::max(blocks.size(), other.blocks.size());
    result.blocks.resize(n, 0);

    for (size_t i = 0; i < n; ++i) {
        int sum = carry;
        if (i < blocks.size()) sum += blocks[i];
        if (i < other.blocks.size()) sum += other.blocks[i];

        carry = sum / base;
        sum %= base;

        result.blocks[i] = sum;
    }

    if (carry > 0) {
        result.blocks.push_back(carry);
    }

    while (!result.blocks.empty() && result.blocks.back() == 0) {
        result.blocks.pop_back();
    }

    return result;
}


BigInt BigInt::handleDifferentSignsSubtraction(const BigInt& other) const {
    BigInt result;

    if (blocks.size() < other.blocks.size()) {
        result = other;
    } else {
        result = *this;
    }

    if (blocks.size() < other.blocks.size()) {
        result.sign = -result.sign;
    }

    for (size_t i = 0; i < std::min(blocks.size(), other.blocks.size()); ++i) {
        result.blocks[i] -= other.blocks[i];

        if (result.blocks[i] < 0) {
            result.blocks[i] += base;
            --result.blocks[i + 1];
        }
    }

    result.removeLeadingZeros();

    return result;
}

// // Toán tử trừ
// BigInt BigInt::operator-(const BigInt& other) const {
//     // Triển khai phép trừ tại đây
//     return BigInt();  // Kết quả tạm thời
// }


BigInt BigInt::operator-(const BigInt& other) const {
    if (blocks.empty() || other.blocks.empty()) {
        return BigInt("0");
    }

    if (sign != other.sign) {
        return handleDifferentSignsSubtraction(other);
    }

    BigInt result = *this;
    result.sign *= -1;
    result.blocks.resize(std::max(result.blocks.size(), other.blocks.size()), 0);

    for (size_t i = 0; i < other.blocks.size(); ++i) {
        result.blocks[i] -= other.blocks[i];

        if (result.blocks[i] < 0) {
            result.blocks[i] += base;
            --result.blocks[i + 1];
        }
    }

    result.removeLeadingZeros();

    return result;
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
BigInt BigInt::pow(const BigInt& power) const {
    // Triển khai phương thức lũy thừa tại đây
    return BigInt();  // Kết quả tạm thời
}


// // Ghi dữ liệu ra ostream

// std::ostream& operator<<(std::ostream& os, const BigInt& bigint) {
//     os << "BigInt: ";
//     if (bigint.sign == -1) {
//         os << "-";
//     }
//     for (long i = bigint.blocks.size() - 1; i >= 0; i--) {
//         os << bigint.blocks[i];
//         if (i > 0) {
//             os << " ";
//         }
//     }
//     return os;
// }

// // Phương thức chuyển đổi BigInt thành chuỗi
// std::string BigInt::to_string() const {
//     std::string result;
//     if (sign == -1) {
//         result += "-";
//     }
//     for (long i = blocks.size() - 1; i >= 0; i--) {
//         result += std::to_string(blocks[i]);
//     }
//     return result;
// }


std::ostream& operator<<(std::ostream& os, const BigInt& bigint) {
    os << "BigInt: ";
    os << ((bigint.sign == -1) ? "-" : "");
    for (long i = bigint.blocks.size() - 1; i >= 0; i--) {
        os << bigint.blocks[i];
        if (i > 0) {
            os << " ";
        }
    }
    return os;
}

std::string BigInt::to_string() const {
    std::string result = (sign == -1) ? "-" : "";
    for (long i = blocks.size() - 1; i >= 0; i--) {
        result += std::to_string(blocks[i]);
    }
    return result;
}

// void BigInt::removeLeadingZeros() {
//     while (blocks.size() > 1 && blocks.back() == 0) {
//         blocks.pop_back();
//     }
// }


// Các phương thức trợ giúp khác có thể được thêm vào tại đây
