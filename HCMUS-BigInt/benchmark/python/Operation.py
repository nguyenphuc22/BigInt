from unittest import result

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

class Operation:
    def __init__(self, line):
        self.line = line
        self.result = None
        self.num2 = None
        self.operation = None
        self.num1 = None
        self.order = None
        self.parse()

    def parse(self):
        # Parse the line into components
        components = self.line.split(',')
        self.order = int(components[0])
        self.num1 = int(components[1])
        self.operation = int(components[2])
        self.num2 = int(components[3])
        self.result = int(components[4])

    def execute(self):
        # Execute the operation described by the components
        # This is just a placeholder, you'll need to replace it with your actual execution logic
        return self.performOperation()

    def performOperation(self):
        if self.operation == 1:
            re = self.num1 + self.num2
        elif self.operation == 2:
            re = self.num1 - self.num2
        elif self.operation == 3:
            re = self.num1 * self.num2
        elif self.operation == 4:
            from decimal import Decimal, getcontext

            getcontext().prec = 100  # Set the precision to 100

            num1 = Decimal(str(self.num1))
            num2 = Decimal(str(self.num2))

            re = num1 / num2

        elif self.operation == 5:
            re = self.num1 % self.num2
        elif self.operation == 6:
            if self.num1 == 0 and self.num2 < 0:
                return 'inf'  # or raise an error
            else:
                re = self.num1 ** self.num2
        else:
            return "Unknown operation"

        return int(re)