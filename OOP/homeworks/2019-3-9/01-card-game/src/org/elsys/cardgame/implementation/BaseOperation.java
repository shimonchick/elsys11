package org.elsys.cardgame.implementation;

import org.elsys.cardgame.api.Deck;
import org.elsys.cardgame.api.Operation;

public abstract class BaseOperation implements Operation {

    String name;
    Deck deck;

    public BaseOperation(String name, Deck deck) {
        this.name = name;
        this.deck = deck;
    }

    @Override
    public String getName() {
        return this.name;
    }

    public abstract void execute();

}
