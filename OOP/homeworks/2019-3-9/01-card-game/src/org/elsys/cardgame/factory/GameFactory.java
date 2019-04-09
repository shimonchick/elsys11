package org.elsys.cardgame.factory;

import org.elsys.cardgame.api.Card;
import org.elsys.cardgame.api.Deck;
import org.elsys.cardgame.api.Game;
import org.elsys.cardgame.implementation.BaseGame;
import org.elsys.cardgame.implementation.BeloteDeck;
import org.elsys.cardgame.implementation.SantasseDeck;
import org.elsys.cardgame.implementation.WarDeck;

import java.util.ArrayList;
import java.util.List;

public class GameFactory {

    public static Game createWarGame(List<Card> cards) {
        List<Card> warGameCards = DeckFactory.defaultWarDeck().getCards();
//        warGameCards.removeAll(cards);
//        if (warGameCards.size() != 0) {
//            System.out.println("ERROR: Not enough cards for War");
//            return null;
//        }
        //cards.stream().filter((card -> warGameCards.contains(card)));
        warGameCards = DeckFactory.defaultWarDeck().getCards();
        List<Card> allowedCards = new ArrayList<>();
        for (Card c : cards) {
            if (warGameCards.contains(c)) {
                allowedCards.add(c);
            }
        }
        if (allowedCards.size() < DeckFactory.defaultWarDeck().handSize()) {
            System.out.println("ERROR: Not enough cards for War");
            return null;
        }
        Deck deck = new WarDeck(allowedCards);
        //System.out.println(allowedCards.toArray().toString());
        return new BaseGame(deck);


    }

    public static Game createSantasseGame(List<Card> cards) {
        List<Card> santasseGameCards = DeckFactory.defaultSantasseDeck().getCards();
//        santasseGameCards.removeAll(cards);
//        if (santasseGameCards.size() != 0) {
//            System.out.println("ERROR: Not enough cards for Santasse");
//            return null;
//        }
        //cards.stream().filter((card -> warGameCards.contains(card)));
        santasseGameCards = DeckFactory.defaultSantasseDeck().getCards();
        List<Card> allowedCards = new ArrayList<>();
        for (Card c : cards) {
            if (santasseGameCards.contains(c)) {
                allowedCards.add(c);
            }
        }
        if (allowedCards.size() < DeckFactory.defaultSantasseDeck().handSize()) {
            System.out.println("ERROR: Not enough cards for War");
            return null;
        }
        Deck deck = new SantasseDeck(allowedCards);
//        System.out.println(allowedCards.toArray().toString());
        return new BaseGame(deck);

    }

    public static Game createBeloteGame(List<Card> cards) {
        List<Card> beloteGameCards = DeckFactory.defaultBeloteDeck().getCards();
//        beloteGameCards.removeAll(cards);
//        if (beloteGameCards.size() != 0) {
//            System.out.println("ERROR: Not enough cards for Belote");
//            return null;
//        }
        //cards.stream().filter((card -> warGameCards.contains(card)));
        beloteGameCards = DeckFactory.defaultBeloteDeck().getCards();
        List<Card> allowedCards = new ArrayList<>();
        for (Card c : cards) {
            if (beloteGameCards.contains(c)) {
                allowedCards.add(c);
            }
        }
        if (allowedCards.size() < DeckFactory.defaultBeloteDeck().handSize()) {
            System.out.println("ERROR: Not enough cards for War");
            return null;
        }
        Deck deck = new BeloteDeck(allowedCards);

        //System.out.println(allowedCards.toArray().toString());
        return new BaseGame(deck);

    }
}