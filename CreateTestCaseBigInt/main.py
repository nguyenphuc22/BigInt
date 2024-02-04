# This is a sample Python script.
import os

# Press ⌃R to execute it or replace it with your code.
# Press Double ⇧ to search everywhere for classes, files, tool windows, actions, and settings.

# 1 +
# 2 -
# 3 *
# 4 /
# 5 %
# 6 pow
# Create Define
Add = 1
Sub = 2
Mul = 3
Div = 4
Mod = 5
Pow = 6
Smaller = 7
Equal = 8
Larger = 9
LessThanEqual = 10
LargerThanEqual = 11
other = 12

def print_hi(name):
    # Use a breakpoint in the code line below to debug your script.
    print(f'Hi, {name}')  # Press ⌘F8 to toggle the breakpoint.
# Đây là hàm tạo số nguyên lớn, có thể là âm hoặc dương
import random

def generate_bigint(length):
    return int(''.join([str(random.randint(0, 9)) for _ in range(length)]))


def randomBigInt(operation, range=10**64):
    if operation == Pow:
        return random.randint(2, 10**3)  # Adjust this range as needed for Pow operation
    else:
        return random.randint(-range, range)

def getFileName(operation):
    if operation == Add:
        return "add.txt"
    elif operation == Sub:
        return "sub.txt"
    elif operation == Mul:
        return "mul.txt"
    elif operation == Div:
        return "div.txt"
    elif operation == Mod:
        return "mod.txt"
    elif operation == Pow:
        return "pow.txt"
    elif operation == Smaller:
        return "smaller.txt"
    elif operation == Equal:
        return "equal.txt"
    elif operation == Larger:
        return "larger.txt"
    elif operation == LessThanEqual:
        return "lessThanEqual.txt"
    elif operation == LargerThanEqual:
        return "largerThanEqual.txt"
    elif operation == other:
        return "other.txt"
    else:
        return "unknown.txt"

def fast_power(base, power):
    result = 1
    while power > 0:
        # If power is odd
        if power % 2 == 1:
            result = result * base
        # Divide the power by 2
        power = power // 2
        # Multiply base to itself
        base = base * base
    return result


def performOperation(operation, num1, num2):
    if operation == Add:
        result = num1 + num2
    elif operation == Sub:
        result = num1 - num2
    elif operation == Mul:
        result = num1 * num2
    elif operation == Div:
        result = num1 // num2
    elif operation == Mod:
        result = num1 % num2
    elif operation == Pow:
        if num1 == 0 and num2 < 0:
            return 'inf'  # or raise an error
        else:
            result = num1 ** num2
    else:
        return "Unknown operation"

    # Convert the result to int before returning
    return int(result)

def performCompare(operation, num1, num2):
    if operation == Smaller:
        result = num1 < num2
    elif operation == Equal:
        result = num1 == num2
    elif operation == Larger:
        result = num1 > num2
    elif operation == LessThanEqual:
        result = num1 <= num2
    elif operation == LargerThanEqual:
        result = num1 >= num2
    else:
        result = num1 != num2
    return result

def createFileTestCaseBigInt(loop,operation):
    directory = "data"
    if not os.path.exists(directory):
        os.makedirs(directory)
    name = directory + "/" + getFileName(operation)
    for i in range(loop):
        special = random.randint(0, 4)
        if special == 0 and operation != Div and operation != Mod and operation != Pow:
            numberA = randomBigInt(operation=operation)
            numberB = 0
        elif special == 1 and operation != Div and operation != Mod and operation != Pow:
            numberA = 0
            numberB = randomBigInt(operation=operation)
        elif special == 2:
            numberA = randomBigInt(operation=operation)
            numberB = randomBigInt(operation=operation)
        elif special == 3:
            numberA = randomBigInt(operation=operation)
            numberB = randomBigInt(operation=operation,range=10**32)
        elif special == 4:
            numberA = randomBigInt(operation=operation,range=10**32)
            numberB = randomBigInt(operation=operation)
        else:
            numberA = randomBigInt(operation=operation)
            numberB = randomBigInt(operation=operation)
            
        # Export file txt with format: i,numberA,Add,numberB,numberA + numberB
        file = open(name, "a")
        print(str(i) + "," + str(numberA) + "," + str(operation) + "," + str(numberB) + "," + str(performOperation(operation,numberA,numberB)))
        file.write(str(i) + "," + str(numberA) + "," + str(operation) + "," + str(numberB) + "," + str(performOperation(operation,numberA,numberB)) + "\n")

def createFileTestCaseBigIntCompare(loop,operation):
    directory = "data"
    if not os.path.exists(directory):
        os.makedirs(directory)
    name = directory + "/" + getFileName(operation)
    for i in range(loop):
        numberA = randomBigInt(operation=operation)
        numberB = randomBigInt(operation=operation)
        # Export file txt with format: i,numberA,Add,numberB,numberA + numberB
        file = open(name, "a")
        print(str(i) + "," + str(numberA) + "," + str(operation) + "," + str(numberB) + "," + str(performCompare(operation,numberA,numberB)))
        file.write(str(i) + "," + str(numberA) + "," + str(operation) + "," + str(numberB) + "," + str(performCompare(operation,numberA,numberB)) + "\n")

# Press the green button in the gutter to run the script.
if __name__ == '__main__':
    createFileTestCaseBigInt(1000,Add)
    createFileTestCaseBigInt(1000,Sub)
    createFileTestCaseBigInt(1000,Mul)
    createFileTestCaseBigInt(1000,Div)
    createFileTestCaseBigInt(1000,Mod)
    createFileTestCaseBigInt(1000,Pow)
    createFileTestCaseBigIntCompare(1000,Smaller)
    createFileTestCaseBigIntCompare(1000,Equal)
    createFileTestCaseBigIntCompare(1000,Larger)
    createFileTestCaseBigIntCompare(1000,LessThanEqual)
    createFileTestCaseBigIntCompare(1000,LargerThanEqual)
    createFileTestCaseBigIntCompare(1000,other)
    print_hi('PyCharm')
