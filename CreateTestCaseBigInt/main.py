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

def print_hi(name):
    # Use a breakpoint in the code line below to debug your script.
    print(f'Hi, {name}')  # Press ⌘F8 to toggle the breakpoint.
# Đây là hàm tạo số nguyên lớn, có thể là âm hoặc dương
import random

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
        result = num1 / num2
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

def createFileTestCaseBigInt(loop,operation):
    directory = "data"
    if not os.path.exists(directory):
        os.makedirs(directory)
    name = directory + "/" + getFileName(operation)
    for i in range(loop):
        numberA = randomBigInt(operation=operation)
        numberB = randomBigInt(operation=operation)
        # Export file txt with format: i,numberA,Add,numberB,numberA + numberB
        file = open(name, "a")
        print(str(i) + "," + str(numberA) + "," + str(operation) + "," + str(numberB) + "," + str(performOperation(operation,numberA,numberB)))
        file.write(str(i) + "," + str(numberA) + "," + str(operation) + "," + str(numberB) + "," + str(performOperation(operation,numberA,numberB)) + "\n")

# Press the green button in the gutter to run the script.
if __name__ == '__main__':
    createFileTestCaseBigInt(100,Add)
    createFileTestCaseBigInt(100,Sub)
    createFileTestCaseBigInt(100,Mul)
    createFileTestCaseBigInt(100,Div)
    createFileTestCaseBigInt(100,Mod)
    createFileTestCaseBigInt(100,Pow)
    print_hi('PyCharm')
