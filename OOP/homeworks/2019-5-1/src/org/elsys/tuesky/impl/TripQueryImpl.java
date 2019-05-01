package org.elsys.tuesky.impl;

import org.elsys.tuesky.api.planner.Query;
import org.elsys.tuesky.api.planner.TripQuery;
import org.elsys.tuesky.api.trips.Trip;

public class TripQueryImpl implements TripQuery {

    Query query;

    public TripQueryImpl(Query query) {
        this.query = query;
    }

    @Override
    public boolean matches(Trip trip) {
        return query.matches(trip);
    }
    public TripQuery and(TripQuery other){
        return new TripQueryImpl(trip -> query.matches(trip) && other.matches(trip));
    }

    public TripQuery or(TripQuery other){
        return new TripQueryImpl(trip -> query.matches(trip) || other.matches(trip));

    }

    public TripQuery not(){
        return new TripQueryImpl(trip -> !query.matches(trip));
    }

}
