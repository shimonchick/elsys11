package org.elsys.cardgame.implementation;

import org.elsys.cardgame.api.Deck;

public class SortOperation extends BaseOperation {
    public SortOperation(String name, Deck deck) {
        super(name, deck);
    }

    @Override
    public void execute() {
        this.deck.sort();
    }
}
