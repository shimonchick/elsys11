package org.elsys.cardgame.factory;

import org.elsys.cardgame.api.Deck;
import org.elsys.cardgame.implementation.BeloteDeck;
import org.elsys.cardgame.implementation.SantasseDeck;
import org.elsys.cardgame.implementation.WarDeck;

public class DeckFactory {

	public static Deck defaultWarDeck() {
		return new WarDeck();
	}

	public static Deck defaultSantasseDeck() {

		return new SantasseDeck();
	}

	public static Deck defaultBeloteDeck() {

		return new BeloteDeck();
	}
}
