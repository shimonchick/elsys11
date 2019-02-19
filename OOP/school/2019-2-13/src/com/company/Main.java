package com.company;

import java.util.Scanner;

public class Main {

    public static void main(String[] args) {
	    first();
    }

    private static void first(){
        Scanner scanner = new Scanner(System.in);
        while(scanner.hasNextLine()){
            String line = scanner.nextLine();
            System.out.println(line);
        }
    }
}
