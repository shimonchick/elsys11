package org.elsys.tuesky.api.trips;

import org.elsys.tuesky.api.planner.Query;
import org.elsys.tuesky.api.planner.TripQuery;

import java.time.Duration;
import java.util.List;

public interface Trip {

    String getOrigin();

    String getDestination();

    Duration getDuration();

    Duration getLayoverDuration();

    int getFlightsCount();

    boolean matches(TripQuery query);

    List<TripUnit> getSubtrips();

//    List<TripUnit> getSubtrips();
}
