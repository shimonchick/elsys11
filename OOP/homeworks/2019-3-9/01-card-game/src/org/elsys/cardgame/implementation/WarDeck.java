package org.elsys.cardgame.implementation;

import org.elsys.cardgame.api.Rank;

import java.util.Arrays;
import java.util.List;

public class WarDeck extends BaseDeck {


    private static final int HAND_MAX_SIZE = 26;
    private static final List<Rank> allowedRanks  = Arrays.asList(Rank.values());

    public WarDeck() {
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
