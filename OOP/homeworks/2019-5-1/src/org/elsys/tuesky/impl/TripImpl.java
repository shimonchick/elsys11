package org.elsys.tuesky.impl;

import org.elsys.tuesky.api.planner.TripQuery;
import org.elsys.tuesky.api.trips.Flight;
import org.elsys.tuesky.api.trips.Layover;
import org.elsys.tuesky.api.trips.Trip;
import org.elsys.tuesky.api.trips.TripUnit;

import java.time.Duration;
import java.util.*;

public final class TripImpl implements Trip {

    private final List<TripUnit> subTrips;
    private final Duration duration;
    private final Duration layoverDuration;
    private final int flightsCount;

    public TripImpl(List<TripUnit> subTrips) {
        this.subTrips = subTrips;

        duration = subTrips.stream()
                .map(TripUnit::getDuration)
                .reduce(Duration.ZERO, Duration::plus);
        layoverDuration = subTrips.stream()
                .filter(tripUnit -> tripUnit instanceof Layover)
                .map(TripUnit::getDuration)
                .reduce(Duration.ZERO, Duration::plus);
        flightsCount = (int) subTrips.stream()
                .filter(tripUnit -> tripUnit instanceof Flight)
                .count();
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof TripImpl)) return false;
        TripImpl trip = (TripImpl) o;
        return Objects.equals(subTrips, trip.subTrips);
    }

    @Override
    public int hashCode() {
        return Objects.hash(subTrips);
    }

    @Override
    public String getOrigin() {
        return ((Flight) this.subTrips.get(0)).getOrigin();
    }

    @Override
    public String getDestination() {
        return ((Flight) this.subTrips.get(this.subTrips.size() - 1)).getDestination();
    }

    @Override
    public Duration getDuration() {
        return duration;
    }

    @Override
    public Duration getLayoverDuration() {
        return layoverDuration;
    }

    @Override
    public int getFlightsCount() {
        return flightsCount;
    }

    @Override
    public boolean matches(TripQuery query) {
        return query.matches(this);
    }

    public List<TripUnit> getSubtrips() {
        return this.subTrips;
    }

}
