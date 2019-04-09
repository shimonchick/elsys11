package org.elsys.cardgame.implementation;

import org.elsys.cardgame.api.CardException;
import org.elsys.cardgame.api.Deck;

public class TopCardOperation extends BaseOperation {
    public TopCardOperation(String name, Deck deck) {
        super(name, deck);
    }

    @Override
    public void execute() {
        try {
            System.out.println(this.deck.topCard());

        } catch(IndexOutOfBoundsException e){
            throw new CardException("ERROR: Not enough cards in deck");
        }
    }
}
