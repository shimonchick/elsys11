package com.company;

public enum Gender {
    MALE("m"),
    FEMALE("f"),
    APACHE_HELICOPTER("a");

    private final String name;

    Gender(String name){
        this.name = name;
    }

    public static Gender getGender(String name){
        return Gender.valueOf(name);
    }

    public String getName() {
        return name;
    }

    @Override
    public String toString() {
        return name;
    }
}
