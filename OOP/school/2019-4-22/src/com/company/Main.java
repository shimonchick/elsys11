package com.company;

import java.io.BufferedReader;
import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;
import java.util.stream.Collectors;

public class Main {

    public static void main(String[] args) {
	    List<Person> personList = createPersonFromCSV("persons.csv");
        personList.forEach(p -> System.out.println(p.toString()));
        List<String> womenUnder25 = personList.stream()
                .filter(person -> person.getAge() < 25 && person.getGender() == Gender.FEMALE)
                .map(person -> person.getFirstName().concat(person.getLastName()))
                .collect(Collectors.toList());
        womenUnder25.forEach(System.out::println);

        String reduceNames = personList.stream()
                .map(person -> person.getFirstName().concat(person.getLastName()))
                .reduce("", (l, r) -> l + "," + r + "\n");

        int ageSum = personList.stream()
                .map(person -> person.getAge())
                .reduce(0, (l, r)-> l + r);
        System.out.println(ageSum);

    }

    private static List<Person> createPersonFromCSV(String filename){
        List<Person> result = new ArrayList<>();

        Path pathToFile = Paths.get(filename);

        try(BufferedReader bufferedReader = Files.newBufferedReader(pathToFile, StandardCharsets.US_ASCII)) {
            String line = bufferedReader.readLine();
            while(line != null){
                String[] attributes = line.replaceAll(" ", "").split(",");
                result.add(createPersonFromString(attributes));
                line = bufferedReader.readLine();
            }
            return result;
        }catch (IOException e){
            System.out.println(e);

        }

        return result;
    }

    private static Person createPersonFromString(String[] atributes){
        String firstName = atributes[0];
        String lastName = atributes[1];
        int age = Integer.parseInt(atributes[2]);
        Gender gender = atributes[3].equals("m")? Gender.MALE: atributes[3].equals("f")? Gender.FEMALE: Gender.APACHE_HELICOPTER;
        return new Person(firstName, lastName, age, gender);
    }
}
