package org.elsys.tuesky.impl.planner;

import org.elsys.tuesky.api.planner.Planner;
import org.elsys.tuesky.api.planner.TripQuery;
import org.elsys.tuesky.api.trips.Trip;
import org.elsys.tuesky.impl.Factory;
import org.elsys.tuesky.impl.Trips;
import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.Test;

import java.time.Duration;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.List;

public class PlannerTest {
    private static List<Trip> trips;

    @BeforeAll
    public static void initialize() {
        Assertions.assertDoesNotThrow(() -> {
            trips = new LinkedList<>();
            trips.add(Factory.startTrip()
                    .then(Factory.createFlight("Sofia", "Athens", Duration.ofHours(1)))
                    .then(Factory.createLayover(Duration.ofMinutes(90)))
                    .then(Factory.createFlight("Athens", "Xania", Duration.ofHours(1)))
                    .end());
            trips.add(Factory.startTrip()
                    .then(Factory.createFlight("Sofia", "Athens", Duration.ofHours(1)))
                    .end());
            trips.add(Factory.startTrip()
                    .then(Factory.createFlight("Sofia", "Eindhoven", Duration.ofHours(1)))
                    .then(Factory.createLayover(Duration.ofMinutes(90)))
                    .then(Factory.createFlight("Eindhoven", "London", Duration.ofHours(1)))
                    .then(Factory.createLayover(Duration.ofMinutes(210)))
                    .then(Factory.createFlight("London", "Havana", Duration.ofHours(10)))
                    .end());
        });

    }

    @Test
    public void testSearch() {
        Planner planner = Factory.createPlanner(trips);
        TripQuery query = Trips.withDestination("Havana");
        List<Trip> results = planner.search(query);
        Assertions.assertEquals(results.get(0), trips.get(2));

    }

    @Test
    public void testAnyMatch() {
        Planner planner = Factory.createPlanner(trips);
        TripQuery query = Trips.withMaxDuration(Duration.ofMinutes(59));
        boolean result = planner.anyMatch(query);
        Assertions.assertEquals(result, false);

    }

    @Test
    public void testCount() {
        Planner planner = Factory.createPlanner(trips);
        TripQuery query = Trips.withMaxFlights(2);
        int results = planner.count(query);
        Assertions.assertEquals(results, 2);

    }
}
