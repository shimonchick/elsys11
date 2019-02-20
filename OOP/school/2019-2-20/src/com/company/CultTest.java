package com.company;

import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Test;

import java.util.Arrays;
import java.util.List;

public class CultTest {
    @Test
    public void testGetMembersBySubscription(){
        Member mihael = new Member("Mihael", 20.0);
        Cult cult = new Cult(new Member("Smbd", 0.0),
                "Elsys",
                Arrays.asList(
                        mihael,

                        new Member("Mishu", 0.0),
                        new Member("Prasu", 5.0),
                        new Member("fhauidp", 2.0)
                ));

        List<Member> ordered = cult.getMembersOrderBySubscription();
        final int actual = ordered.indexOf((mihael));
        Assertions.assertEquals(4, actual);
    }
}
