const bigInt = require('big-integer');

class Calculation {
    constructor(order, firstNumber, operation, secondNumber, result) {
        this.order = order;
        this.firstNumber = bigInt(firstNumber);
        this.operation = operation;
        this.secondNumber = bigInt(secondNumber);
        this.result = bigInt(result);
    }

    static parseFromLine(line) {
        const parts = line.split(",");
        const order = parseInt(parts[0]);
        const firstNumber = parts[1];
        const operation = parseInt(parts[2]);
        const secondNumber = parts[3];
        const result = parts[4];
        return new Calculation(order, firstNumber, operation, secondNumber, result);
    }

    execute() {
        switch (this.operation) {
            case 1:
                return this.firstNumber.add(this.secondNumber);
            case 2:
                return this.firstNumber.subtract(this.secondNumber);
            case 3:
                return this.firstNumber.multiply(this.secondNumber);
            case 4:
                return this.firstNumber.divide(this.secondNumber);
            case 5:
                return this.firstNumber.mod(this.secondNumber);
            case 6:
                return this.firstNumber.pow(this.secondNumber);
            default:
                return 0;
        }
    }

    getOrder() {
        return this.order;
    }

    getFirstNumber() {
        return this.firstNumber;
    }

    getOperation() {
        switch (this.operation) {
            case 1:
                return "+";
            case 2:
                return "-";
            case 3:
                return "*";
            case 4:
                return "/";
            case 5:
                return "%";
            default:
                throw new Error("Unknown operation: " + this.operation);
        }
    }

    getSecondNumber() {
        return this.secondNumber;
    }

    getResult() {
        return this.result;
    }
}

module.exports = Calculation;