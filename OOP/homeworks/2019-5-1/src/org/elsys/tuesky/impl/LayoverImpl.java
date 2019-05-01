package org.elsys.tuesky.impl;

import org.elsys.tuesky.api.trips.Layover;
import org.elsys.tuesky.api.trips.TripUnit;

import java.time.Duration;

public class LayoverImpl extends TripUnitImpl implements Layover {


    private TripUnit next;
    private TripUnit prev;

    public LayoverImpl(Duration duration) {
        super(duration);
    }

    @Override
    public TripUnit getNext() {
        return next;
    }

    @Override
    public TripUnit getPrev() {
        return prev;
    }

    @Override
    public void setNext(TripUnit next)  {
        this.next = next;
    }

    @Override
    public void setPrev(TripUnit prev)  {
        this.prev = prev;
    }
}
