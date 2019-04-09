package org.elsys.cardgame.implementation;

import org.elsys.cardgame.api.CardException;
import org.elsys.cardgame.api.Deck;

public class DrawTopCardOperation extends BaseOperation{

    public DrawTopCardOperation(String name, Deck deck) {
        super(name, deck);
    }

    @Override
    public void execute() throws CardException{
        if(this.deck.getCards().size() == 0){
            throw new CardException("ERROR: Not enough cards in deck");
        }
        this.deck.drawTopCard();
    }
}
