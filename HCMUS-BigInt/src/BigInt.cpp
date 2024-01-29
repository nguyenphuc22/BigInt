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

//////////////////////////////// PHẦN CỦA VIÊN ////////////////////////////////////////////
// Toán tử cộng
BigInt BigInt::operator+(const BigInt& other) const {
    BigInt result;
    //Kiểm tra xem có phải cả hai số đều là số không
    if (this->blocks.empty() || (other.blocks.empty())) {
        return BigInt("0");
    }

    // Trường hợp 1 số "0" cộng cho số lớn 
    if (this->blocks.size() == 1 &&  this->blocks[0] == 0){
        return other;
    }
    if (other.blocks.size() == 1 && other.blocks[0] == 0){
        return *this;
    }

    // Trường hợp cộng cùng dấu 
    if (this->sign == other.sign){
        result.sign = this->sign;
        int carry = 0;  // Biến nhớ khi cộng
        size_t n = std::max(this->blocks.size(), other.blocks.size());
        result.blocks.resize(n, 0); // Khởi tạo các blocks với giá trị 0

        for (size_t i = 0; i < n; ++i) {
            int sum = carry;
            if (i < this->blocks.size()) sum += this->blocks[i];
            if (i < other.blocks.size()) sum += other.blocks[i];

            carry = sum / base;  // Tính carry
            sum %= base;         // Giữ lại phần dưới của block

            result.blocks[i] = sum;
        }

        if (carry > 0) {
            result.blocks.push_back(carry);
        }        
    } else {    // Trường hợp trái dấu
        BigInt tempOther = other;
        tempOther.sign *= -1; // Đảo dấu của 'other'
        
        // Xác định số nào lớn hơn và thực hiện phép trừ
        if (isLargerThan(*this, tempOther)) {
            result = *this - tempOther;
            result.sign = this->sign;
        } else {
            result = tempOther - *this;
            result.sign = other.sign;
        }        
    }

    // Xóa các blocks dư thừa ở cuối
    while (!result.blocks.empty() && result.blocks.back() == 0) {
        result.blocks.pop_back();
    }

    return result;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////
BigInt BigInt::operator-(const BigInt& other) const {
    BigInt result;
    //Kiểm tra xem có phải cả hai số đều là số không
    if (this->blocks.empty() || (other.blocks.empty())) {
        return BigInt("0");
    }

    // Trường hợp 1 số "0" trừ cho số lớn 
    if (this->blocks.size() == 1 &&  this->blocks[0] == 0){
        return other;
    }
    if (other.blocks.size() == 1 && other.blocks[0] == 0){
        return *this;
    }

    // Trường hợp trừ cùng dấu
    if (this->sign == other.sign) {
        result.sign = this->sign;
        const BigInt* larger = nullptr;
        const BigInt* smaller = nullptr;

        if (isLargerThan(*this, other)) {
            larger = this;
            smaller = &other;
            result.sign = this->sign;
        } else {
            larger = &other;
            smaller = this;
            result.sign = -this->sign;
        }

        result.blocks.resize(larger->blocks.size(), 0);
        int borrow = 0;
        for (size_t i = 0; i < larger->blocks.size(); ++i) {
            int diff = larger->blocks[i] - borrow - (i < smaller->blocks.size() ? smaller->blocks[i] : 0);
            borrow = 0;
            if (diff < 0) {
                diff += base;
                borrow = 1;
            }
            result.blocks[i] = diff;
        }
    }else {     // Trường hợp trừ khác dấu
        BigInt tempOther = other;
        tempOther.sign *= -1; // Đảo dấu của 'other'
        
        // Xác định số nào lớn hơn và thực hiện phép trừ
        if (isLargerThan(*this, tempOther)) {
            result = *this + tempOther;
            result.sign = this->sign;
        } else {
            result = tempOther + *this;
            result.sign = other.sign;
        }  
    }
        // Loại bỏ các số 0 không cần thiết ở cuối
    while (!result.blocks.empty() && result.blocks.back() == 0) {
        result.blocks.pop_back();
    }

    return result;

}
// Hàm so sánh độ lớn
bool BigInt::isLargerThan(const BigInt& a, const BigInt& b) const {
    // So sánh độ dài của vector
    if (a.blocks.size() != b.blocks.size()) {
        return a.blocks.size() > b.blocks.size();
    }
    // So sánh từng block
    for (int i = a.blocks.size() - 1; i >= 0; i--) {
        if (a.blocks[i] != b.blocks[i]) {
            return a.blocks[i] > b.blocks[i];
        }
    }
    return false;  // Hai số bằng nhau
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
