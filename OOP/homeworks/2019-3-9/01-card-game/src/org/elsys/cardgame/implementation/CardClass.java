package org.elsys.cardgame.implementation;
import org.elsys.cardgame.api.Rank;
import org.elsys.cardgame.api.Suit;

import java.util.Objects;

public class CardClass implements org.elsys.cardgame.api.Card {

    Suit suit;
    Rank rank;

    public CardClass(Suit suit, Rank rank) {
        this.suit = suit;
        this.rank = rank;
    }

    @Override
    public Suit getSuit() {
        return this.suit;
    }

    @Override
    public Rank getRank() {
        return this.rank;
    }

    @Override
    public String toString() {
        return "" + suit + rank;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof CardClass)) return false;
        CardClass cardClass = (CardClass) o;
        return getSuit() == cardClass.getSuit() &&
                getRank() == cardClass.getRank();
    }

    @Override
    public int hashCode() {
        return Objects.hash(getSuit(), getRank());
    }
}
