package org.elsys.cardgame.implementation;

import org.elsys.cardgame.api.Card;

import java.util.List;

public class HandClass implements org.elsys.cardgame.api.Hand {

    List<Card> cards;

    public HandClass(List<Card> cards) {
        this.cards = cards;
    }

    @Override
    public List<Card> getCards() {
        return this.cards;
    }

    @Override
    public int size() {
        return this.cards.size();
    }
}
