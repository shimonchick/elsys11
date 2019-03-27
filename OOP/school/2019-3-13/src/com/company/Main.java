package com.company;

import java.util.HashSet;

public class Main {

    public static void main(String[] args) {
        HashSet<Member> employees = new HashSet<>();
        employees.add(new Member(1, 1, "Ivan"));
        Member ivan2 = new Member(2, 1, "Ivan");
        employees.add(ivan2);
        Integer
        System.out.println(employees);
        ivan2.setId(1);
        System.out.println(employees);
    }
}
