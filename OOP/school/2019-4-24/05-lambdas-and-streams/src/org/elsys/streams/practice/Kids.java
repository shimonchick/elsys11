package org.elsys.streams.practice;

import java.util.List;
import java.util.Map;
import java.util.Set;
import java.util.stream.Collector;
import java.util.stream.Collectors;

public class Kids {

    public static Set<String> getKidNames(List<Person> people) {
        return people.stream().filter(person -> {
            return person.getAge() < 18;
        }).map(person -> {
            return person.getName();
        }).collect(Collectors.toSet());
    }

    public static Map<String, Integer> getKidsAgeByName(List<Person> people) {
        return people.stream().filter(person -> {
            return person.getAge() < 18;
        }).collect(Collectors.toMap(p -> p.getName(), p-> p.getAge(), (p1, p2)-> p1));

    }
}
