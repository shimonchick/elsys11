package org.elsys.streams.practice;

import java.util.List;
import java.util.stream.Collectors;

public class Joining {

    public static String namesToString(List<Person> people) {
        return people.stream().map(person -> person.getName()).collect(Collectors.joining(", ", "Names: ", "."));

    }

}
