package org.elsys.streams.practice;

import java.util.List;
import java.util.stream.Collectors;

public class ToUpperCase {

    public static List<String> transform(List<String> collection) {
        return collection.stream().map((it) -> {
            return it.toUpperCase();
        }).collect(Collectors.toList());
    }

}
