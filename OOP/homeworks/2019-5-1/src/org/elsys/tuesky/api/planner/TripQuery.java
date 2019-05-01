package org.elsys.tuesky.api.planner;

import org.elsys.tuesky.api.trips.Trip;

import java.util.List;

public interface TripQuery {

    boolean matches(Trip trip);

    TripQuery and(TripQuery other);

    TripQuery or(TripQuery other);

    TripQuery not();
}
