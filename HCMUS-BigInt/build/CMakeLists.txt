cmake_minimum_required(VERSION 3.10)
project(HCMUS-BigInt)

# Đặt chuẩn C++ (ví dụ: C++14)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Thêm thư mục chứa các file header
include_directories(include)

# Tìm tất cả các file nguồn trong thư mục src và thêm chúng vào biến
file(GLOB SOURCES "../src/main.cpp")

file(GLOB TEST_SOURCES "../tests/testCase.cpp")

# Tạo một target thực thi từ các file nguồn
add_executable(HCMUS-BigInt ${SOURCES})

# Tạo một target thực thi từ các file nguồn
add_executable(HCMUS-BigInt-Test ${TEST_SOURCES})

add_executable(BenchMark
        ../benchmark/cplusplus/BenchMark.cpp
)

add_executable(BenchMark-Test
        ../benchmark/cplusplus/HelloWorld.cpp
)
