package org.elsys.streams.practice;

import java.util.Collections;
import java.util.List;

public class OldestPerson {

    public static Person getOldestPerson(List<Person> people) {
        return people.stream().reduce(people.get(0), (person, person2) -> {
            return person.getAge() > person2.getAge()? person : person2;
        });
    }

}
