package org.elsys.cardgame.implementation;

import org.elsys.cardgame.api.*;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;

public abstract class BaseDeck implements Deck {

    protected Hand hand;

    protected List<Card> cards;

    public BaseDeck() {
        this.cards = new ArrayList<Card>();
        this.hand = new HandClass(new ArrayList<Card>());
        for (Suit s : Suit.values()) {
            for (Rank r : getAllowedRanks()) {
                Card c = new CardClass(s, r);
                this.cards.add(c);
            }
        }
//        for (Card c : cards) {
//            System.out.println(c.toString());
//        }
    }

    public BaseDeck(List<Card> cards) {
        this.cards = cards;
        //this.sort();
        this.hand = new HandClass(new ArrayList<>());
    }

    protected abstract List<Rank> getAllowedRanks();

    protected abstract int getHandMaxSize();

    @Override
    public List<Card> getCards() {
        return this.cards;
    }

    @Override
    public int size() {
        return this.cards.size();
    }

    @Override
    public int handSize() {
        return this.hand.size();
    }

    @Override
    public Card drawTopCard() {
        return cards.remove(0);
    }

    @Override
    public Card topCard()
    {
        return cards.get(0);
    }

    @Override
    public Card drawBottomCard() {
        return cards.remove(cards.size() - 1);
    }

    @Override
    public Card bottomCard() {
        return cards.get(cards.size() - 1);
    }

    @Override
    public Hand deal() {
        List<Card> cardsToDeal = new ArrayList<Card>();
        for (int i = 0; i < getHandMaxSize(); i++) {
            cardsToDeal.add(this.cards.get(i)); // get the weakest cards

        }

        this.cards.subList(0, getHandMaxSize()).clear();

        this.hand = new HandClass(cardsToDeal);

        return this.hand;
    }

    @Override
    public void sort() {
        this.cards.sort(new Comparator<Card>() {
            @Override
            public int compare(Card c1, Card c2) {
                if (c1.getSuit().compareTo(c2.getSuit()) == 0) {
                    if (getAllowedRanks().indexOf(c1.getRank()) > getAllowedRanks().indexOf(c2.getRank())) {
                        return 1;
                    } else if (getAllowedRanks().indexOf(c1.getRank()) < getAllowedRanks().indexOf(c2.getRank())) {
                        return -1;
                    } else {
                        return 0;
                    }
                } else return c1.getSuit().compareTo(c2.getSuit());
            }
        });

    }

    public void shuffle() {
        Collections.shuffle(this.cards);
    }
}
