package com.company;

import java.util.LinkedList;
import java.util.List;

public class Person {
    private String firstName;
    private String lastName;
    private int age;
    private List<Person> friend;

    @Override
    public String toString() {
        return "Person{" +
                "firstName='" + firstName + '\'' +
                ", lastName='" + lastName + '\'' +
                ", age=" + age +
                ", friend=" + friend +
                ", gender=" + gender +
                '}';
    }

    private Gender gender;

    public Person(String firstName, String lastName, int age, Gender gender) {
        this.firstName = firstName;
        this.lastName = lastName;
        this.age = age;
        this.friend = new LinkedList<Person>();
        this.gender = gender;
    }

    public String getFirstName() {
        return firstName;
    }

    public void setFirstName(String firstName) {
        this.firstName = firstName;
    }

    public String getLastName() {
        return lastName;
    }

    public void setLastName(String lastName) {
        this.lastName = lastName;
    }

    public int getAge() {
        return age;
    }

    public void setAge(int age) {
        this.age = age;
    }

    public List<Person> getFriend() {
        return friend;
    }

    public void setFriend(List<Person> friend) {
        this.friend = friend;
    }

    public Gender getGender() {
        return gender;
    }

    public void setGender(Gender gender) {
        this.gender = gender;
    }
}
