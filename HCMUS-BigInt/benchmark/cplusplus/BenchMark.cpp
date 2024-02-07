//
// Created by Phuc Nguyen on 06/02/2024.
//

#include <fstream>
#include <chrono>
#include "Operation.cpp"



int main(int argc, char* argv[]) {
    // Testing the BigInt class
    std::string path = "../../../CreateTestCaseBigInt/data/mul.txt";
    std::cerr << "Path: " << path << std::endl;

    // Read input from file CreateTestCaseBigInt/data/add.txt
    std::ifstream inputFile(path);
    if (!inputFile) {
        std::cerr << "Unable to open file";
        return 1; // return with error code 1
    }

    std::vector<std::string> lines;
    std::string line;

    while (std::getline(inputFile, line)) {
        lines.push_back(line);
    }

    inputFile.close();

    std::vector<Operation> ops;

    for (const auto& line : lines) {
        Operation op;
        op.parse(line);

        // Add the Operation object to the vector
        ops.push_back(op);
    }

    long long totalElapsed = 0;

    for (const auto& op : ops) {
        auto start = std::chrono::high_resolution_clock::now();

        std::string cal = op.execute().to_string();

        auto end = std::chrono::high_resolution_clock::now();

        std::cout << op.getOrder() << ": " << op.getFirstNumber().to_string() << " " << op.getOperation() << " " << op.getSecondNumber().to_string() << " = " << op.getResult().to_string() << std::endl;
        std::cout << "Result: " << cal << std::endl;

        auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        totalElapsed += elapsed;
    }

    std::cout << "Total time elapsed: " << totalElapsed << " microseconds" << std::endl;

    return 0;
}