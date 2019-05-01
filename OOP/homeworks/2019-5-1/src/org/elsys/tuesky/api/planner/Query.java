package org.elsys.tuesky.api.planner;

import org.elsys.tuesky.api.trips.Trip;

@FunctionalInterface
public interface Query {
    boolean matches(Trip trip);

}
