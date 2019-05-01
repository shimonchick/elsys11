package org.elsys.tuesky.impl;

import org.elsys.tuesky.api.planner.TripQuery;
import org.elsys.tuesky.api.trips.Flight;
import org.elsys.tuesky.api.trips.Layover;
import org.elsys.tuesky.api.trips.Trip;
import org.elsys.tuesky.api.trips.TripUnit;

import java.time.Duration;
import java.util.List;
import java.util.Objects;

public class TripImpl implements Trip {

    private List<Flight> flights;

    public List<Flight> getFlights() {
        return flights;
    }

    public List<Layover> getLayovers() {
        return layovers;
    }

    private List<Layover> layovers;

    public TripImpl(List<Flight> flights, List<Layover> layovers) {
        this.flights = flights;
        this.layovers = layovers;

    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof TripImpl)) return false;
        TripImpl trip = (TripImpl) o;
        return Objects.equals(flights, trip.flights) &&
                Objects.equals(layovers, trip.layovers);
    }

    @Override
    public int hashCode() {
        return Objects.hash(flights, layovers);
    }

    @Override
    public String getOrigin() {
        return this.flights.get(0).getOrigin();
    }

    @Override
    public String getDestination() {
        return this.flights.get(this.flights.size() - 1).getDestination();
    }

    @Override
    public Duration getDuration() {
         final Duration flightDuration = this.flights.stream()
                .map(flight -> flight.getDuration())
                .reduce(Duration.ofDays(0), (duration, duration2) -> duration.plus(duration2));
         final Duration layoverDuration = getLayoverDuration();
         return flightDuration.plus(layoverDuration);
    }

    @Override
    public Duration getLayoverDuration() {
        return this.layovers.stream()
                .map(layover -> layover.getDuration())
                .reduce(Duration.ofDays(0), (duration, duration2) -> duration.plus(duration2));
    }

    @Override
    public int getFlightsCount() {
        return this.flights.size();
    }

    @Override
    public boolean matches(TripQuery query) {
        return query.matches(this);
    }
}
