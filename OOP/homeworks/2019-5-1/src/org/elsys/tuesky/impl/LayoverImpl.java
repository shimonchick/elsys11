package org.elsys.tuesky.impl;

import org.elsys.tuesky.api.trips.Layover;
import org.elsys.tuesky.api.trips.TripUnit;

import java.time.Duration;

public final class LayoverImpl extends TripUnitImpl implements Layover {


    public LayoverImpl(Duration duration) {
        super(duration);
    }
}
