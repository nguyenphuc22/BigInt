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


// ================================================= Addition ========================================================================================== //

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




// =========================================================================================================================================== //



// ------------------------------------------ Subtraction ---------------------------------------------------------------------- //


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



// ---------------------------------------------------------------------------------------------------------------- //


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


// ---------------------------------------------------------------------------------------------------------------- //
// ------------------------------------ Multiplication ---------------------------------------------------------------------------- //
// ---------------------------------------------------------------------------------------------------------------- //


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



// bool BigInt::isSmall() const {
//     // Assuming base is 10^6 and each block represents a part of the number
//     // A BigInt is considered small if it has only one block and that block is less than the base
//     if (blocks.size() == 1 && abs(blocks[0]) < base) {
//         return true;
//     }
//     return false;
// }

// // Helper methods not fully implemented for brevity
// BigInt BigInt::getHighPart(size_t m2) const {
//     // Calculate the number of blocks corresponding to m2 digits
//     size_t numBlocks = m2 / std::log10(base);
//     if (numBlocks >= blocks.size()) return BigInt("0"); // High part is 0 if m2 exceeds or equals the size

//     vector<int> highPartBlocks(blocks.end() - numBlocks, blocks.end());
//     return BigInt(highPartBlocks, sign);
// }

// BigInt BigInt::getLowPart(size_t m2) const {
//     size_t numBlocks = m2 / std::log10(base);
//     vector<int> lowPartBlocks(blocks.begin(), blocks.size() > numBlocks ? blocks.end() - numBlocks : blocks.end());
//     return BigInt(lowPartBlocks, sign);
// }

// BigInt BigInt::shiftLeft(size_t m) const {
//     // m is the number of digits to shift by, so convert that to the number of blocks
//     size_t numBlocks = m / std::log10(base);
//     std::vector<int> shiftedBlocks = blocks;
//     for (size_t i = 0; i < numBlocks; ++i) {
//         shiftedBlocks.insert(shiftedBlocks.begin(), 0); // Insert zeros at the beginning
//     }
//     return BigInt(shiftedBlocks, sign);
// }

// BigInt BigInt::simpleMultiply(const BigInt& a, const BigInt& b) const {
//     BigInt product;
//     product.sign = a.sign * b.sign;
//     product.blocks.resize(a.blocks.size() + b.blocks.size(), 0);

//     for (size_t i = 0; i < a.blocks.size(); ++i) {
//         long long carry = 0;
//         for (size_t j = 0; j < b.blocks.size() || carry; ++j) {
//             long long sum = product.blocks[i + j] + carry + 
//                             a.blocks[i] * (j < b.blocks.size() ? b.blocks[j] : 0);
//             product.blocks[i + j] = sum % base;
//             carry = sum / base;
//         }
//     }

//     product.removeLeadingZeros();
//     return product;
// }

// BigInt BigInt::karatsubaMultiply(const BigInt& x, const BigInt& y) const {
//     // Base case: if one of the numbers is small, use simple multiplication
//     if (x.isSmall() || y.isSmall()) {
//         return simpleMultiply(x, y);
//     }

//     size_t m = std::max(x.blocks.size(), y.blocks.size()) / 2; // Split position

//     // Splitting x and y
//     BigInt high1 = x.getHighPart(m);
//     BigInt low1 = x.getLowPart(m);
//     BigInt high2 = y.getHighPart(m);
//     BigInt low2 = y.getLowPart(m);

//     // Recursive steps
//     BigInt z0 = karatsubaMultiply(low1, low2); // bd
//     BigInt z1 = karatsubaMultiply(low1 + high1, low2 + high2); // (a+b)(c+d)
//     BigInt z2 = karatsubaMultiply(high1, high2); // ac

//     // Combine the results: 10^(2*m)*z2 + 10^m*(z1 - z2 - z0) + z0
//     BigInt result = z2.shiftLeft(2 * m) + ((z1 - z2 - z0).shiftLeft(m)) + z0;

//     result.sign = x.sign * y.sign; // Set the correct sign
//     result.removeLeadingZeros(); // Remove any leading zeros
//     return result;
// }

// BigInt BigInt::operator*(const BigInt& other) const {
//     // Check for zero multiplication
//     if (this->isZero() || other.isZero()) {
//         return BigInt("0");
//     }

//     // Optimize multiplication for small numbers
//     if (this->blocks.size() == 1 && other.blocks.size() == 1) {
//         return this->simpleMultiply(*this, other);
//     }

//     // Use Karatsuba algorithm for larger numbers
//     return this->karatsubaMultiply(*this, other);
// }



// ---------------------------------------------------------------------------------------------------------------- //
// ---------------------------------------------------------------------------------------------------------------- //
// ---------------------------------------------------------------------------------------------------------------- //


void BigInt::removeLeadingZeros() {
    while (!blocks.empty() && blocks.back() == 0) {
        blocks.pop_back();
    }
    if (blocks.empty()) {
        sign = 0; // Adjust sign for zero
    }
}


// ---------------------------------------------------------------------------------------------------------------- //
// ------------------------------------------ division ---------------------------------------------------------------------- //
// ---------------------------------------------------------------------------------------------------------------- //


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



// void BigInt::removeLeadingZeros4divice() {
//     while (!blocks.empty() && blocks.back() == 0) {
//         blocks.pop_back();
//     }
//     if (blocks.empty()) {
//         // Adjust sign for zero
//         sign = 1; // Zero is not negative.
//         blocks.push_back(0); // Ensure there's a zero in the blocks for a BigInt representing 0
//     }
// }

// BigInt BigInt::operator/(const BigInt& divisor) const {
//     if (divisor.isZero()) {
//         throw std::invalid_argument("Division by zero.");
//     }

//     if (this->isZero() || *this < divisor) {
//         return BigInt("0"); // Result is 0 if dividend is 0 or less than divisor
//     }

//     BigInt dividend = *this;
//     BigInt quotient;
//     quotient.blocks.clear(); // Ensure quotient starts empty
//     quotient.sign = (this->sign == divisor.sign) ? 1 : -1; // Determine sign of the quotient

//     BigInt curr;
//     int currPosition = 0;

//     // Start from the most significant part of the dividend
//     for (int i = dividend.blocks.size() - 1; i >= 0; --i) {
//         // // Shift current number left by base and add the new digit
//         // curr = curr * base + BigInt(std::to_string(dividend.blocks[i]));
//         curr = curr * BigInt(std::to_string(base)) + BigInt(std::to_string(dividend.blocks[i]));

//         curr.removeLeadingZeros4divice();

//         int count = 0;
//         // Subtract divisor from current number until it's smaller than divisor
//         while (curr >= divisor) {
//             curr = curr - divisor;
//             ++count;
//         }

//         // Insert count into the correct position of the result
//         if (currPosition < quotient.blocks.size()) {
//             quotient.blocks[quotient.blocks.size() - 1 - currPosition] = count;
//         } else {
//             quotient.blocks.insert(quotient.blocks.begin(), count);
//         }
//         ++currPosition;
//     }

//     quotient.removeLeadingZeros4divice();
//     return quotient;
    
// }


// ---------------------------------------------------------------------------------------------------------------- //
// ---------------------------------------------------------------------------------------------------------------- //
// ---------------------------------------------------------------------------------------------------------------- //


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


// BigInt& operator+=(const BigInt& other) {
//     // Implement addition logic here
//     *this = *this + other; // Use the already defined operator+
//     return *this;
// }


// ---------------------------------------------------------------------------------------------------------------- //
// -------------------------------------------- Modulus -------------------------------------------------------------------- //
// ---------------------------------------------------------------------------------------------------------------- //


// Static function definition
// Returns the absolute value of a BigInt.
BigInt BigInt::abs(const BigInt& num) {
    BigInt result = num; // Make a copy of num
    // Ensure the result is always non-negative, except for zero which remains unchanged.
    result.sign = (result.sign != 0) ? 1 : result.sign; // Adjust sign to positive, except for zero
    // result.sign = (result.sign != 1) ? 0 : result.sign; // Adjust sign to positive, except for zero
    return result;
}

// BigInt BigInt::operator%(const BigInt& divisor) const {
//     if (divisor == BigInt("0")) {
//         throw std::invalid_argument("Modulus by zero is undefined.");
//     }

//     // Directly return zero for these special cases
//     if (*this == BigInt("0") || divisor == BigInt("1") || divisor == BigInt("-1")) {
//         return BigInt("0");
//     }

//     // Calculate the remainder: remainder = dividend - (quotient * divisor)
//     BigInt remainder = *this - ((*this / divisor) * divisor);

//     // Adjust the sign of the remainder to match the dividend
//     // If the remainder is negative and the divisor is positive, adjust the remainder
//     if (remainder.sign < 0 && divisor.sign > 0) {
//         remainder = remainder + BigInt::abs(divisor);
//     }

//     // // Ensure the remainder's sign matches the dividend's
//     // remainder.sign = this->sign;

//     // Normalize zero remainder to have zero sign
//     if (remainder.isZero()) {
//         remainder.sign = 0;
//     }

//     return remainder;
// }


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
        // remainder += BigInt::abs(divisor);
        remainder = remainder + BigInt::abs(divisor);
    }
    // Similarly, adjust when remainder is positive but the divisor is negative.
    else if (remainder.sign > 0 && divisor.sign < 0) {
        // remainder -= BigInt::abs(divisor);
        remainder = remainder - BigInt::abs(divisor);
    }

    // Ensure the remainder's sign matches the divisor's
    if (!remainder.isZero()) {
        remainder.sign = divisor.sign;
    }

    return remainder;
}


// ---------------------------------------------------------------------------------------------------------------- //
// ---------------------------------------------------------------------------------------------------------------- //
// ---------------------------------------------------------------------------------------------------------------- //



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



