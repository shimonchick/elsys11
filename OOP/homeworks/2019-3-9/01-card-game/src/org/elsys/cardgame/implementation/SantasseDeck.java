package org.elsys.cardgame.implementation;

import org.elsys.cardgame.api.*;

import java.util.*;

import static org.elsys.cardgame.api.Rank.*;

public class SantasseDeck extends BaseDeck {

    private static final int HAND_MAX_SIZE = 6;
    private static final List<Rank> allowedRanks = Arrays.asList(NINE, JACK, QUEEN, KING, TEN, ACE);

    public SantasseDeck(List<Card> allowedCards) {
        super(allowedCards);
    }
    public SantasseDeck(){
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
