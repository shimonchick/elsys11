package org.elsys.tuesky.impl;

import org.elsys.tuesky.api.trips.*;

import java.util.LinkedList;
import java.util.List;

public class TripBuilderImpl implements TripBuilder {
    private List<Flight> flightList;
    private List<Layover> layoverList;

    public TripBuilderImpl() {
        this.flightList = new LinkedList<>();
        this.layoverList = new LinkedList<>();
    }

    @Override
    public TripBuilder then(TripUnit nextUnit) throws Exception {
        if (nextUnit instanceof Flight) {
            if(this.flightList.size() > 0){
                this.flightList.get(this.flightList.size() - 1).setNext(nextUnit);
                nextUnit.setPrev(this.flightList.get(this.flightList.size() - 1));
            }
            this.flightList.add((Flight) nextUnit);
        } else {
            if(this.layoverList.size() > 0){
                this.layoverList.get(this.layoverList.size() - 1).setNext(nextUnit);
                nextUnit.setPrev(this.layoverList.get(this.layoverList.size() - 1));
            }

            this.layoverList.add((Layover) nextUnit);
        }
        return this;
    }

    @Override
    public Trip end() {
        return new TripImpl(this.flightList, this.layoverList);
    }
}
