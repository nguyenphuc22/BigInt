package org.example;

import java.util.ArrayList;
import java.util.List;

public class Main {
    public static void main(String[] args) {

        FileReader fileReader = new FileReader();

        List<String> lines = fileReader.readFile("../../../../CreateTestCaseBigInt/data/div.txt");

        ArrayList<Calculation> calculations = new ArrayList<>();

        for (String line : lines) {
            calculations.add(Calculation.parseFromLine(line));
        }

        long totalDuration = 0;

        for (Calculation calculation : calculations) {
            long startTime = System.nanoTime();
            String calculated = calculation.execute().toString();
            long endTime = System.nanoTime();

            System.out.println(calculation.getFirstNumber() + " " + calculation.getOperation() + " " + calculation.getSecondNumber());
            System.out.println("Expected: " + calculation.getResult());
            System.out.println("Calculated: " + calculated);

            long duration = (endTime - startTime) / 1000;
            totalDuration += duration;
        }

        System.out.println("Total execution time in microseconds: " + totalDuration);
    }


}

