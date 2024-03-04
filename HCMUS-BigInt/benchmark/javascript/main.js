const fs = require('fs');
const performance = require('perf_hooks').performance;
const Calculation = require('./Calculation');

let paths = [
    "../../../CreateTestCaseBigInt/data/add.txt",
    // "../../../CreateTestCaseBigInt/data/sub.txt",
    // "../../../CreateTestCaseBigInt/data/mul.txt",
    // "../../../CreateTestCaseBigInt/data/div.txt",
    // "../../../CreateTestCaseBigInt/data/mod.txt",
    // "../../../CreateTestCaseBigInt/data/pow.txt"
];

for (let path of paths) {
    console.log("File: " + path);

    let lines = null

    try {
        lines = fs.readFileSync(path, 'utf-8').split('\n');
    } catch (e) {
        console.error(e);
    }

    let calculations = [];

    for (let line of lines) {
        calculations.push(Calculation.parseFromLine(line));
    }

    let totalDuration = 0;

    for (let calculation of calculations) {
        let startTime = performance.now();
        let calculated = calculation.execute().toString();
        let endTime = performance.now();

        if (calculated !== calculation.getResult().toString()) {
            console.log("Incorrect");
            return;
        }

        let duration = (endTime - startTime) * 1000;
        totalDuration += duration;
    }

    console.log("Total execution time in microseconds: " + totalDuration);
}