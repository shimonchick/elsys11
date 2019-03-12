package org.elsys.cardgame.implementation;

import org.elsys.cardgame.api.Rank;

import java.util.Arrays;
import java.util.List;

import static org.elsys.cardgame.api.Rank.*;
public class BeloteDeck extends BaseDeck {

    private static final List<Rank> allowedRanks = Arrays.asList(SEVEN, EIGHT, NINE, JACK, QUEEN, KING,TEN, ACE);
    private static final int HAND_MAX_SIZE = 8;

    public BeloteDeck() {
        super();
    }

    @Override
    protected List<Rank> getAllowedRanks() {
        return allowedRanks;
    }

    @Override
    protected int getHandMaxSize() {
        return HAND_MAX_SIZE;
    }


}
