package org.example;

import java.math.BigInteger;

public class Calculation {

    private int order;
    private BigInteger firstNumber;
    private int operation;
    private BigInteger secondNumber;
    private BigInteger result;

    public Calculation(int order, BigInteger firstNumber, int operation, BigInteger secondNumber, BigInteger result) {
        this.order = order;
        this.firstNumber = firstNumber;
        this.operation = operation;
        this.secondNumber = secondNumber;
        this.result = result;
    }

    public static Calculation parseFromLine(String line) {
        String[] parts = line.split(",");
        int order = Integer.parseInt(parts[0]);
        BigInteger firstNumber = new BigInteger(parts[1]);
        int operation = Integer.parseInt(parts[2]);
        BigInteger secondNumber = new BigInteger(parts[3]);
        BigInteger result = new BigInteger(parts[4]);
        return new Calculation(order, firstNumber, operation, secondNumber, result);
    }

    public BigInteger execute() {
        switch (operation) {
            case 1:
                return firstNumber.add(secondNumber);
            case 2:
                return firstNumber.subtract(secondNumber);
            case 3:
                return firstNumber.multiply(secondNumber);
            case 4:
                return firstNumber.divide(secondNumber);
            default:
                throw new IllegalArgumentException("Unknown operation: " + operation);
        }
    }

    public int getOrder() {
        return order;
    }

    public BigInteger getFirstNumber() {
        return firstNumber;
    }

    public String getOperation() {
        switch (operation) {
            case 1:
                return "+";
            case 2:
                return "-";
            case 3:
                return "*";
            case 4:
                return "/";
            default:
                throw new IllegalArgumentException("Unknown operation: " + operation);
        }
    }

    public BigInteger getSecondNumber() {
        return secondNumber;
    }

    public BigInteger getResult() {
        return result;
    }
}