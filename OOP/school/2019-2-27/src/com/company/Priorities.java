package com.company;

import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;
import java.util.Scanner;

public class Priorities {
    public List<Student> getStudents(List<String> events){
        List<Student> students = new ArrayList<Student>();
        for(String event: events) {
            Scanner scanner = new Scanner(event);
            String type = scanner.next();
            if(type.equals("ENTER")){
                String name = scanner.next();
                double cgpa = scanner.nextDouble();
                int id = scanner.nextInt();
                students.add(new Student(id, name, cgpa));
            }
            else if(type.equals("SERVED")){
                students.sort(new Comparator<Student>() {
                    @Override
                    public int compare(Student s1, Student s2) {
                        if(s1.getCGPA() > s2.getCGPA()){
                            return 1;
                        }
                        else if(s1.getCGPA() < s2.getCGPA()){
                            return -1;
                        }
                        else{
                            if(s1.getName().compareTo(s2.getName()) == 0){
                                if(s1.getID() > s1.getID()){
                                    return 1;
                                }
                                else if(s1.getID() < s2.getID()){
                                    return -1;
                                }
                                else{
                                    return 0;
                                }
                            }
                            else{
                                return s1.getName().compareTo(s2.getName());
                            }
                        }
                    }
                });

                students.remove(0);
            }
        }
        return students;
    }
}
