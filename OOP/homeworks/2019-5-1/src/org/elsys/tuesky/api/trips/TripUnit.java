package org.elsys.tuesky.api.trips;

import java.time.Duration;

public interface TripUnit {

    Duration getDuration();

    TripUnit getNext();

    TripUnit getPrev();

    void setNext(TripUnit next) throws Exception;

    void setPrev(TripUnit prev) throws Exception;
}
