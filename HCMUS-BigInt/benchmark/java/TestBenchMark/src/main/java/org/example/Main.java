package org.example;

import java.util.ArrayList;
import java.util.List;

public class Main {
    public static void main(String[] args) {


        List<String> paths = new ArrayList<String>();
        paths.add("../../../../CreateTestCaseBigInt/data/add.txt");
//        paths.add("../../../../CreateTestCaseBigInt/data/sub.txt");
//        paths.add("../../../../CreateTestCaseBigInt/data/mul.txt");
//        paths.add("../../../../CreateTestCaseBigInt/data/div.txt");
//        paths.add("../../../../CreateTestCaseBigInt/data/mod.txt");
//        paths.add("../../../../CreateTestCaseBigInt/data/pow.txt");

        for (String path : paths) {
            System.out.println("File: " + path);
            FileReader fileReader = new FileReader();

            List<String> lines = fileReader.readFile(path);

            ArrayList<Calculation> calculations = new ArrayList<>();

            for (String line : lines) {
                calculations.add(Calculation.parseFromLine(line));
            }

            long totalDuration = 0;

            for (Calculation calculation : calculations) {
                long startTime = System.nanoTime();
                String calculated = calculation.execute().toString();
                long endTime = System.nanoTime();

                if (!calculated.equals(calculation.getResult().toString())) {
                    System.out.println("Incorrect");
                    return;
                }

//                System.out.println(calculation.getFirstNumber() + " " + calculation.getOperation() + " " + calculation.getSecondNumber());
//                System.out.println("Expected: " + calculation.getResult());
//                System.out.println("Calculated: " + calculated);

                long duration = (endTime - startTime) / 1000;
                totalDuration += duration;
            }

            System.out.println("Total execution time in microseconds: " + totalDuration);
        }


    }


}

