package org.elsys.tuesky.impl;

import org.elsys.tuesky.api.trips.TripUnit;

import java.time.Duration;

public abstract class TripUnitImpl implements TripUnit {
    private Duration duration;
    private TripUnit prev;
    private TripUnit next;


    public TripUnitImpl(Duration duration)
    {
        this.duration = duration;
    }

    @Override
    public Duration getDuration() {
        return duration;
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
    public void setNext(TripUnit next){
        this.next = next;

    }

    @Override
    public void setPrev(TripUnit prev) {
        this.prev = prev;

    }

}
