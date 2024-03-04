// BigInt_add_sub_mul.cpp

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
    blocks = from_string(inputString);
}

// Check if BigInt is zero
bool BigInt::isZero() const {
    return blocks.size() == 1 && blocks[0] == 0;
}

// Helper method to correctly set the sign after subtraction
BigInt& BigInt::setSign(int newSign) {
    if (isZero()) sign = 0;
    else sign = newSign;
    return *this;
}

// Negate the BigInt
BigInt BigInt::negate() const {
    BigInt result = *this;
    result.sign = -sign;
    return result;
}


// Helper method to subtract two numbers without considering signs
BigInt BigInt::subtractNumbers(const BigInt& larger, const BigInt& smaller) const {
    BigInt result;
    result.blocks.resize(larger.blocks.size(), 0);
    int borrow = 0;

    for (size_t i = 0; i < larger.blocks.size(); ++i) {
        int a = larger.blocks[i];
        int b = i < smaller.blocks.size() ? smaller.blocks[i] : 0;
        int diff = a - b - borrow;
        borrow = 0;
        if (diff < 0) {
            borrow = 1;
            diff += base;
        }
        result.blocks[i] = diff;
    }

    result.removeLeadingZeros();
    return result;
}

// Method to subtract two BigInt numbers considering their signs
// Enhanced subtraction to account for signs and magnitude 
BigInt BigInt::subtractWithSign(const BigInt& other) const {
    if (sign == other.sign) {
        if (isFirstLargerThanSecond(*this, other)) {
            return subtractNumbers(*this, other).setSign(sign);
        } else {
            return subtractNumbers(other, *this).setSign(-sign);
        }
    }
    // Handling different signs by adding the magnitudes and assigning the sign of the first operand
    return *this + other.negate();
}

// Addition operator
// Optimized addition operator
BigInt BigInt::operator+(const BigInt& other) const {
    if (sign == 0) return other;
    if (other.sign == 0) return *this;
    if (sign != other.sign) return subtractWithSign(-other);

    BigInt result;
    result.sign = sign;
    int carry = 0, sum = 0;
    size_t maxLength = max(blocks.size(), other.blocks.size());

    result.blocks.resize(maxLength);
    for (size_t i = 0; i < maxLength || carry; ++i) {
        sum = carry + (i < blocks.size() ? blocks[i] : 0) + (i < other.blocks.size() ? other.blocks[i] : 0);
        result.blocks[i] = sum % base;
        carry = sum / base;
    }

    if (carry) result.blocks.push_back(carry);
    return result;
}

// Overload unary minus to simplify negation
BigInt BigInt::operator-() const {
    BigInt result = *this;
    result.sign = -sign;
    return result;
}

BigInt BigInt::operator-(const BigInt& other) const {
    BigInt result;

    // Handle zero cases
    if (*this == BigInt("0")) {
        result = other;
        result.sign = -other.sign;
        return result;
    } else if (other == BigInt("0")) {
        return *this;
    }

    // If signs are different, add the numbers
    if (sign != other.sign) {
        return *this + (-other);
    }

    bool thisLarger = isFirstLargerThanSecond(*this, other);
    const BigInt *larger = thisLarger ? this : &other;
    const BigInt *smaller = thisLarger ? &other : this;

    int carry = 0;
    for (size_t i = 0; i < larger->blocks.size() || carry; ++i) {
        int largerBlock = i < larger->blocks.size() ? larger->blocks[i] : 0;
        int smallerBlock = i < smaller->blocks.size() ? smaller->blocks[i] : 0;
        int blockResult = largerBlock - carry - smallerBlock;
        carry = 0;
        if (blockResult < 0) {
            carry = 1;
            blockResult += base;
        }
        if (i < result.blocks.size()) {
            result.blocks[i] = blockResult;
        } else {
            result.blocks.push_back(blockResult);
        }
    }

    result.sign = thisLarger ? sign : -sign;
    result.removeLeadingZeros(); // Remove leading zeros

    // Handle result of zero
    if (result.blocks.empty()) {
        result.sign = 0;
    }

    return result;
}

// Hàm so sánh độ lớn
bool BigInt::isFirstLargerThanSecond(const BigInt& a, const BigInt& b) const {
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
    return this->multiplySameBasicAlgorithm(other);
}

// Phương thức nhân cơ bản
BigInt BigInt::multiplySameBasicAlgorithm(const BigInt& other) const {
    if (this->blocks.size() == 1 && this->blocks[0] == 0) {
        return BigInt("0");
    }

    if (other.blocks.size() == 1 && other.blocks[0] == 0) {
        return BigInt("0");
    }

    BigInt result;


    // Tính toán kích thước của vector kết quả
    // Kích thước của vector kết quả sẽ là tổng của kích thước của 2 vector gốc
    // Ví dụ: 123 * 1234
    // Kích thước của vector kết quả sẽ là 3 + 4 = 7
    result.blocks.resize(this->blocks.size() + other.blocks.size(), 0);

    for (size_t i = 0; i < this->blocks.size(); ++i) {
        int carry = 0;
        for (size_t j = 0; j < other.blocks.size() || carry > 0; ++j) {
            long long block_one = this->blocks[i]; // Ép kiểu block[i] thành long long

            // Kiểm tra null safety cho other.blocks
            long long block_two = 0;
            if (j < other.blocks.size()) {
                block_two = other.blocks[j];
            }

            // Tính toán giá trị hiện tại
            long long currentSum = result.blocks[i + j] + ((block_one * block_two) + carry);

            // Tách giả trị tổng thành phần dư và nguyên
            // Phần dư sẽ là giá trị của block hiện tại
            // Ví dụ: currentSum 1234567
            // Phần dư: 234567
            result.blocks[i + j] = int(currentSum % base);

            // Phần nguyên sẽ là giá trị của carry
            // Ví dụ: currentSum 1234567
            // Phần nguyên: 1
            carry = int(currentSum / base);
        }
    }

    // Gán dấu cho kết quả
    result.sign = this->sign * other.sign;

    // Xóa các số 0 không cần thiết ở cuối
    result.removeLeadingZeros();
    return result;
}

void BigInt::removeLeadingZeros() {
    while (!blocks.empty() && blocks.back() == 0) {
        blocks.pop_back();
    }
    if (blocks.empty()) {
        sign = 0; // Adjust sign for zero
    }
}

// Phép chia cho BigInt
BigInt BigInt::operator/(const BigInt& other) const {
    // Triển khai phép chia tại đây
    return this->divideSameBasicAlgorithm(other);  // Kết quả tạm thời
}

// Thuật toán mượn ý tưởng từ Long division
// https://en.wikipedia.org/wiki/Division_algorithm
// https://en.wikipedia.org/wiki/Long_division#Algorithm_for_arbitrary_base
BigInt BigInt::divideSameBasicAlgorithm(const BigInt &other) const {
    if (other == BigInt("0")) {
        throw std::invalid_argument("Division by zero is not allowed.");
    }

    BigInt result("0");
    // Chuẩn hóa dấu
    BigInt tempA = *this;
    BigInt tempB = other;
    tempB.sign = 1;
    tempA.sign = 1;


    while (tempA >= tempB) {
        BigInt count("1");
        BigInt tempOther = tempB;

        // Tìm số lần số chia "vừa vặn" với số bị chia
        // Nhân số chia với 2 cho đến khi nào lớn hơn số bị chia ( Muốn nhân 3 cũng được, miễn sau giảm lần lập lại)
        // Tui thì đặt nhân 2 bởi vì tui thích :))
        while ((tempOther + tempOther) <= tempA) {
            tempOther = tempOther + tempOther;
            count = count + count;
        }

        tempA = tempA - tempOther;
        result = result + count;
    }

    if (!result.blocks.empty() && result.blocks[0] == 0) {
        result.sign = 0;
    } else {
        result.sign = this->sign * other.sign;
    }
    
    return result;
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

// Static function definition
// Returns the absolute value of a BigInt.
BigInt BigInt::abs(const BigInt& num) {
    BigInt result = num; // Make a copy of num
    // Ensure the result is always non-negative, except for zero which remains unchanged.
    result.sign = (result.sign != 0) ? 1 : result.sign; // Adjust sign to positive, except for zero
    // result.sign = (result.sign != 1) ? 0 : result.sign; // Adjust sign to positive, except for zero
    return result;
}

BigInt BigInt::operator%(const BigInt& divisor) const {
    if (divisor == BigInt("0")) {
        throw std::invalid_argument("Modulus by zero is undefined.");
    }

    // Handle special cases where the result is directly known
    if (*this == BigInt("0") || divisor == BigInt("1") || divisor == BigInt("-1")) {
        return BigInt("0");
    }

    BigInt quotient = *this / divisor;
    BigInt product = quotient * divisor;
    BigInt remainder = *this - product;

    // Adjust the remainder for negative dividends to ensure it has the same sign as the divisor
    // or is zero. This adjustment is necessary when the remainder is negative, and the divisor is positive.
    if (remainder.sign < 0 && divisor.sign > 0) {
        remainder = remainder + BigInt::abs(divisor);
    }
    // Similarly, adjust when remainder is positive but the divisor is negative.
    else if (remainder.sign > 0 && divisor.sign < 0) {
        remainder = remainder - BigInt::abs(divisor);
    }

    // Ensure the remainder's sign matches the divisor's
    if (!remainder.isZero()) {
        remainder.sign = divisor.sign;
    }

    return remainder;
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



