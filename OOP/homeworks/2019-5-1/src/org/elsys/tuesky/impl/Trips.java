package org.elsys.tuesky.impl;

import org.elsys.tuesky.api.planner.Query;
import org.elsys.tuesky.api.planner.TripQuery;
import org.elsys.tuesky.api.trips.Flight;
import org.elsys.tuesky.api.trips.Trip;
import org.elsys.tuesky.api.trips.TripUnit;

import java.time.Duration;
import java.util.List;
import java.util.stream.Collectors;

public class Trips {

    public static TripQuery withOrigin(String origin) {
        return new TripQueryImpl(trip -> trip.getOrigin().equals(origin));
    }

    public static TripQuery withDestination(String destination) {
        return new TripQueryImpl(trip -> trip.getDestination().equals(destination));
    }

    public static TripQuery via(String via) {

        return new TripQueryImpl(trip -> {
            return trip.getSubtrips().stream()
                    .filter(tripUnit -> tripUnit instanceof Flight)
                    .anyMatch(tripUnit -> ((Flight) tripUnit).getOrigin().equals(via)
                            || ((Flight) tripUnit).getDestination().equals(via));
        });
    }

    public static TripQuery withMaxDuration(Duration duration) {
        return new TripQueryImpl(trip -> trip.getDuration().compareTo(duration) <= 0);
    }

    public static TripQuery withMaxLayoverDuration(Duration duration) {
        return new TripQueryImpl(trip -> trip.getLayoverDuration().compareTo(duration) <= 0);
    }

    public static TripQuery withMaxFlights(int flights) {
        return new TripQueryImpl(trip -> trip.getFlightsCount() <= flights);
    }
}
