package org.elsys.tuesky.impl;

import org.elsys.tuesky.api.trips.Flight;
import org.elsys.tuesky.api.trips.TripUnit;

import java.time.Duration;


public class FlightImpl extends TripUnitImpl implements Flight {

    private String origin;
    private String destination;
    private TripUnit prev;
    private TripUnit next;

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

    @Override
    public TripUnit getNext() {
        return prev;
    }

    @Override
    public TripUnit getPrev() {
        return next;
    }

    @Override
    public void setNext(TripUnit next) throws RuntimeException {
        if(next instanceof Flight){
            if(((FlightImpl) next).getOrigin().equals(this.getDestination())){
                this.next = next;
            }
            else{
                throw new RuntimeException();
            }
        }
        else{
            this.next = next;
        }
    }

    @Override
    public void setPrev(TripUnit prev) throws RuntimeException {
        if(prev instanceof Flight){
            if(((FlightImpl) prev).getDestination().equals(this.getOrigin())){
               this.prev = prev;
            }
            else{
                throw new RuntimeException();
            }
        }
        else{
            this.prev = prev;
        }
    }
}
