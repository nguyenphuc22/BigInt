//
// Created by Phuc Nguyen on 06/02/2024.
//

#include <fstream>
#include <chrono>
#include "Operation.cpp"



int main(int argc, char* argv[]) {
    // list paths
    std::vector<std::string> paths;
    paths.push_back("../../../CreateTestCaseBigInt/data/add.txt");
//    paths.push_back("../../../CreateTestCaseBigInt/data/sub.txt");
//    paths.push_back("../../../CreateTestCaseBigInt/data/mul.txt");
//    paths.push_back("../../../CreateTestCaseBigInt/data/div.txt");
//    paths.push_back("../../../CreateTestCaseBigInt/data/mod.txt");
//    paths.push_back("../../../CreateTestCaseBigInt/data/pow.txt");

    for (const auto& path: paths) {
        // Testing the BigInt class
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

//            if (op.getResult().to_string() != cal) {
//                std::cerr << "Error at order " << op.getOrder() << std::endl;
//                std::cerr << "Expected: " << op.getResult().to_string() << std::endl;
//                std::cerr << "Got: " << cal << std::endl;
//                return 1;
//            }

//            std::cout << op.getOrder() << ": " << op.getFirstNumber().to_string() << " " << op.getOperation() << " " << op.getSecondNumber().to_string() << " = " << op.getResult().to_string() << std::endl;
//            std::cout << "Result: " << cal << std::endl;

            auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
            totalElapsed += elapsed;
        }

        std::cout << "Total time elapsed: " << totalElapsed << " microseconds" << std::endl;

    }


    return 0;
}