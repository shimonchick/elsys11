package org.elsys.cardgame.implementation;

import org.elsys.cardgame.api.Card;
import org.elsys.cardgame.api.CardException;
import org.elsys.cardgame.api.Deck;
import org.elsys.cardgame.api.Hand;

public class DealOperation extends BaseOperation {
    private Hand hand;

    public DealOperation(String name, Deck deck, Hand hand) {
        super(name, deck);
        this.hand = hand;
    }

    @Override
    public void execute() throws CardException {
        if(this.deck.size() < this.deck.handSize() || this.deck.size() == 0){

            throw new CardException("ERROR: Not enough cards in deck");
        }
        this.hand = this.deck.deal();
        for(Card c : hand.getCards()){
            System.out.printf("%s%s ", c.getSuit(), c.getRank());
        }
        System.out.println();
    }

    public Hand getHand() {

        return this.hand;
    }
}
