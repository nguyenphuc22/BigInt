import time

start_time = time.time()

for _ in range(100000):
    print("Hello World", end="")

end_time = time.time()

elapsed_time = (end_time - start_time) * 1000000  # Convert to microseconds
print(f"\nTotal time elapsed: {elapsed_time} microseconds")