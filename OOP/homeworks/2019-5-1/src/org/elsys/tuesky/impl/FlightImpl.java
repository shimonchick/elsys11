package org.elsys.tuesky.impl;

import org.elsys.tuesky.api.trips.Flight;
import org.elsys.tuesky.api.trips.TripUnit;

import java.time.Duration;


public final class FlightImpl extends TripUnitImpl implements Flight {

    private final String origin;
    private final String destination;

    public FlightImpl(String origin, String destination, Duration duration) {
        super(duration);
        this.origin = origin;
        this.destination = destination;
    }


    @Override
    public String getOrigin() {
        return origin;
    }

    @Override
    public String getDestination() {
        return destination;
    }

}
