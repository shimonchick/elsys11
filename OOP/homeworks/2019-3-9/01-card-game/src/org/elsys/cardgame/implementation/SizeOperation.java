package org.elsys.cardgame.implementation;

import org.elsys.cardgame.api.Deck;

public class SizeOperation extends BaseOperation {
    public SizeOperation(String name, Deck deck) {
        super(name, deck);
    }

    @Override
    public void execute() {
        this.deck.size();
    }
}
