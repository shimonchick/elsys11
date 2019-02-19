package org.elsys;

import java.util.ArrayList;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.List;

public class Main {

    public static void main(String[] args) {
        Student misho = new Student(1, "Mihail", "Kirov");
        List<Student> studentArrayList = new LinkedList<Student>();
        studentArrayList.add(misho);
        studentArrayList.add(new Student(2, "Prasu", "Prasu"));
        System.out.println(studentArrayList);
        System.out.println(
                    studentArrayList.
                            contains(new Student(1, "Mihail", "Kirov"))
        );
        Student somebody = new Student(1, "Mihail", "Kirov");
        System.out.println(misho.hashCode());
        System.out.println(somebody.hashCode());

        HashSet<Student> studentHashSet = new HashSet<Student>();

        studentHashSet.add(somebody);
        System.out.println(studentHashSet);
        HashSet


    }
}
