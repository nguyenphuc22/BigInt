package org.example;

public class HelloWorld {
    public static void main(String[] args) {
        long startTime = System.nanoTime();

        for (int i = 0; i < 100000; i++) {
            System.out.print("Hello World");
        }

        long endTime = System.nanoTime();

        long elapsedTime = (endTime - startTime) / 1000;  // Convert to microseconds
        System.out.println("\nTotal time elapsed: " + elapsedTime + " microseconds");
    }
}