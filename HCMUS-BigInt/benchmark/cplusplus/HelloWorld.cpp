//
// Created by Phuc Nguyen on 07/02/2024.
//


#include <iostream>
#include <chrono>

int main() {
    auto start_time = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < 100000; i++) {
        std::cout << "Hello World";
    }

    auto end_time = std::chrono::high_resolution_clock::now();

    auto elapsed_time = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
    std::cout << "\nTotal time elapsed: " << elapsed_time << " microseconds" << std::endl;

    return 0;
}