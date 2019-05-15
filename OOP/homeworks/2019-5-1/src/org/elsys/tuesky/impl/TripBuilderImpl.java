package org.elsys.tuesky.impl;

import org.elsys.tuesky.api.trips.*;

import java.util.LinkedList;
import java.util.List;

public class TripBuilderImpl implements TripBuilder {
    private List<TripUnit> subTrips;
    private String lastDestination;

    public TripBuilderImpl() {
        this.subTrips = new LinkedList<>();
    }

    @Override
    public TripBuilder then(TripUnit nextUnit) {
        if(nextUnit instanceof Flight){
            if(this.lastDestination!=null && !((Flight) nextUnit).getOrigin().equals(this.lastDestination)){
                throw new RuntimeException();
            }
            this.lastDestination = ((Flight) nextUnit).getDestination();
        }

        this.subTrips.add(nextUnit);

        return this;
    }

    @Override
    public Trip end() {
        return new TripImpl(this.subTrips);
    }

}
