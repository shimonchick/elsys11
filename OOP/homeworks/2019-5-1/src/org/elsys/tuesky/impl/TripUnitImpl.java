package org.elsys.tuesky.impl;

import org.elsys.tuesky.api.trips.TripUnit;

import java.time.Duration;

public abstract class TripUnitImpl implements TripUnit {
    private final Duration duration;
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

}
