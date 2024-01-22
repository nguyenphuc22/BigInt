//
//  BigInt.cpp
//  BigInt
//
//  Created by Phuc Nguyen on 19/01/2024.
//

#include "../include/BigInt.hpp"
#include <iomanip>

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
    base = 1000000;  // 10^6
    
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
    // Kiểm tra trường hợp số 0
    if (this->sign == 0) return other;
    if (other.sign == 0) return *this;

    // Xử lý trường hợp dấu khác nhau
    // if (this->sign != other.sign) {
    //     // Cần phải triển khai phép trừ
    //     // return *this - (-other);
    // }

    BigInt result;
    result.sign = this->sign; // Dấu của kết quả sẽ giống dấu của số hạng đầu tiên

    int carry = 0; // Biến nhớ khi cộng
    size_t n = std::max(this->blocks.size(), other.blocks.size());

    for (size_t i = 0; i < n  || carry; ++i) {
        int sum = carry;
        if (i < this->blocks.size()) sum += this->blocks[i];
        if (i < other.blocks.size()) sum += other.blocks[i];

        result.blocks.push_back(sum % base); // Lưu giá trị sau khi chia cho base
        carry = sum / base; // Nhớ
    }

    // Loại bỏ các block dư thừa ở cuối (nếu có)
    while (!result.blocks.empty() && result.blocks.back() == 0) {
        result.blocks.pop_back();
    }

    // Trường hợp kết quả là 0
    if (result.blocks.empty()) {
        result.sign = 0;
    }

    return result;
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


BigInt BigInt::operator/(const BigInt& other) const {
    return BigInt();  // Kết quả tạm thời
}

bool BigInt::operator==(const BigInt& other) const {
    return sign == other.sign && blocks == other.blocks;
}

bool BigInt::operator!=(const BigInt& other) const {
    return !(*this == other);
}

bool BigInt::operator<(const BigInt& other) const {
    if (sign != other.sign) {
        return sign < other.sign;
    }

    if (blocks.size() != other.blocks.size()) {
        return (sign == 1) ? blocks.size() < other.blocks.size() : blocks.size() > other.blocks.size();
    }

    for (long i = blocks.size() - 1; i >= 0; i--) {
        if (blocks[i] != other.blocks[i]) {
            return (sign == 1) ? blocks[i] < other.blocks[i] : blocks[i] > other.blocks[i];
        }
    }

    return false; // Các số bằng nhau
}

bool BigInt::operator>(const BigInt& other) const {
    return other < *this;
}

bool BigInt::operator<=(const BigInt& other) const {
    return !(*this > other);
}

bool BigInt::operator>=(const BigInt& other) const {
    return !(*this < other);
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

// Ghi dữ liệu ra ostream
std::ostream& operator<<(std::ostream& os, const BigInt& bigint) {
    
    if (bigint.blocks.empty() || (bigint.blocks.size() == 1 && bigint.blocks[0] == 0)) {
        os << "BigInt: 0";
        return os;
    }

    os << "BigInt: ";
    if (bigint.sign == -1) {
        os << "-";
    }

    // Block đầu tiên
    os << bigint.blocks.back();

    // Các block tiếp theo
    for (long i = bigint.blocks.size() - 2; i >= 0; i--) {
        os << " " << std::setw(6) << std::setfill('0') << bigint.blocks[i];
    }

    return os;
}

// Phương thức chuyển đổi BigInt thành chuỗi
std::string BigInt::to_string() const {
    std::string result;
    if (sign == -1) {
        result += "-";
    }
    for (long i = blocks.size() - 1; i >= 0; i--) {
        result += std::to_string(blocks[i]);
    }
    return result;
}



// Các phương thức trợ giúp khác có thể được thêm vào tại đây
