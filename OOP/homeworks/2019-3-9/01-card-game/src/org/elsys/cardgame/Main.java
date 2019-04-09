package org.elsys.cardgame;

import org.elsys.cardgame.api.*;
import org.elsys.cardgame.factory.GameFactory;
import org.elsys.cardgame.implementation.CardClass;

import java.util.LinkedList;
import java.util.List;
import java.util.Scanner;

public class Main {

    public static Game game = null;

    public static void main(String[] args) {
        System.out.print("> ");
        Scanner scanner = new Scanner(System.in);
        String cardInput = scanner.nextLine();
        Scanner cardsScanner = new Scanner(cardInput);
        List<Card> cards = getCards(cardsScanner);
        System.out.print("> ");
        String command = scanner.nextLine();
        while (!command.equals("quit")) {
            boolean next = false;
            switch (command) {
                case "War":
                    game = GameFactory.createWarGame(cards);
//                    System.out.println("Deck created");
                    next = true;
                    break;
                case "Santasse":
                    game = GameFactory.createSantasseGame(cards);
//                    System.out.println("Deck created");
                    next = true;
                    break;
                case "Belote":
                    game = GameFactory.createBeloteGame(cards);
//                    System.out.println("Deck created");
                    next = true;
                    break;
            }
            if(next){
                System.out.print("> ");
                command = scanner.nextLine();
                continue;
            }
            if (game != null) {
                try {
                    game.process(command);
                } catch (CardException e) {
                    System.out.println(e.getMessage());
                }
            } else {
                System.out.println("ERROR: No deck");
            }
            System.out.print("> ");
            command = scanner.nextLine();
        }
    }

    private static List<Card> getCards(Scanner cardsScanner) {
        List<Card> cards = new LinkedList<>();
        while (cardsScanner.hasNext()) {
            String cardString = cardsScanner.next();
            String cardSuitString = cardString.substring(0, 1);
            String cardRankString = cardString.substring(1, 2);
            Suit cardSuit = null;
            Rank cardRank = null;
            for (Suit s : Suit.values()) {
                if (cardSuitString.equals(s.getSymbol())) {
                    cardSuit = s;
                }
            }
            for (Rank r : Rank.values()) {
                if (cardRankString.equals(r.getSymbol())) {
                    cardRank = r;
                }
            }
            if (cardSuit != null && cardRank != null) {
                cards.add(new CardClass(cardSuit, cardRank));
            }
        }
        return cards;
    }
}