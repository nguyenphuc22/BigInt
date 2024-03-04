import time
from Operation import Operation

def benchmark():
    paths = [
             "../../../CreateTestCaseBigInt/data/add.txt",
             # "../../../CreateTestCaseBigInt/data/mod.txt",
             # "../../../CreateTestCaseBigInt/data/mul.txt",
             # "../../../CreateTestCaseBigInt/data/sub.txt",
             # "../../../CreateTestCaseBigInt/data/div.txt",
             # "../../../CreateTestCaseBigInt/data/pow.txt"
    ]

    for path in paths:
        print(f"Executing operations from {path}")
        # Read input from file
        with open(path, 'r') as file:
            lines = file.readlines()

        # Parse lines into operations
        operations = [Operation(line) for line in lines]

        total_elapsed = 0

        # Execute operations
        for operation in operations:
            start_time = time.time()
            result = operation.execute()
            end_time = time.time()

            if operation.result != result:
                print(f"Operation {operation.line} failed")
                print(f"Expected: {operation.result}, got: {result}")
                print()
                return

            # print(f"${operation.line} \nResult: {result}")
            # print()

            # Calculate elapsed time
            elapsed_time = (end_time - start_time) * 1000000  # Convert to microseconds
            total_elapsed += elapsed_time

        print(f"Total time elapsed: {total_elapsed} microseconds")

if __name__ == "__main__":
    benchmark()