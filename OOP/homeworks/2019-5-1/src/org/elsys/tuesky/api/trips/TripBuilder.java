package org.elsys.tuesky.api.trips;

public interface TripBuilder {

    TripBuilder then(TripUnit nextUnit) throws Exception;

    Trip end();
}
