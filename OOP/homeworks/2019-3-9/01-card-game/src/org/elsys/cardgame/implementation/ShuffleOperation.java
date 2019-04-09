package org.elsys.cardgame.implementation;

import org.elsys.cardgame.api.Deck;

public class ShuffleOperation extends BaseOperation {
    public ShuffleOperation(String name, Deck deck) {
        super(name, deck);
    }

    @Override
    public void execute() {
        this.deck.shuffle();
    }
}
