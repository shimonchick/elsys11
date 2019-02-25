package com.company;

import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Test;

import java.util.Arrays;
import java.util.List;

public class CultTest {
    @Test
    public void testGetMembersBySubscription(){
        Member mihael = new Member("Mihael", 20.0, Member.Rank.INITIATE);
        Cult cult = new Cult(new Member("Smbd", 0.0, Member.Rank.PRIEST),
                "Elsys",
                Arrays.asList(
                        mihael,

                        new Member("Mishu", 0.0, Member.Rank.INITIATE),
                        new Member("Prasu", 5.0),
                        new Member("fhauidp", 2.0)
                ));

        List<Member> ordered = cult.getMembersOrderBySubscription();
        final int actual = ordered.indexOf((mihael));
        Assertions.assertEquals(4, actual);
    }
    @Test
    public void testGetMembersByRanking(){
        Rank initiate = new Rank("Initiate", 1);
        Rank priest = new Rank("Priest", 2);
        Rank wizard = new Rank("Wizard", 3);
        Member mihael = new Member("Mihael", 20.0, Member.Rank.INITIATE);
        Cult cult = new Cult(new Member("Smbd", 0.0, Member.Rank.PRIEST),
                "Elsys",
                Arrays.asList(
                        mihael,

                        new Member("Mishu", 0.0, Member.Rank.INITIATE),
                        new Member("Prasu", 5.0),
                        new Member("fhauidp", 2.0)
                ));

        List<Member> ordered = cult.getMembersOrderBySubscription();
        final int actual = ordered.indexOf((mihael));
        Assertions.assertEquals(4, actual);
    }
}
