package com.company;

import java.util.Scanner;

public class Main {

    public static void main(String[] args) {
	    System.out.printf("args[0] = %s", args[0]);
	    int[] integers = new int[10];
	    readIntegers(integers);

        System.out.println("powers: " + toString(powers(integers)));



    }

    private static int[] powers(int[] integers) {
        int[] result = new int[integers.length];
        for(int i = 0; i < integers.length; i++){
            result[i] = integers[i] * integers[i];
        }
        return result;
    }

    private static void readIntegers(int[] integers){
        Scanner scanner = new Scanner(System.in)
        for(int i = 0; i < integers.length; i++){
            integers[i] = scanner.nextInt();
        }
    }

    public static String toString(int[] integers){
        String result = "";
        for(int value : integers){
            result += value + " ";
        }
        return result;
    }


}
