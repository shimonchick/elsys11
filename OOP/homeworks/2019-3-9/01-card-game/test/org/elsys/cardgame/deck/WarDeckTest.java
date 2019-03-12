package org.elsys.cardgame.deck;

import org.elsys.cardgame.api.Deck;
import org.elsys.cardgame.api.Rank;
import org.elsys.cardgame.factory.DeckFactory;

import java.util.Arrays;
import java.util.List;

public class WarDeckTest extends AbstractDeckTest {


	@Override
	public int deckSize() {
		return 52;
	}

	@Override
	public Deck defaultDeck() {
		return DeckFactory.defaultWarDeck();
	}

	@Override
	public int handSize() {
		return 26;
	}

	@Override
	public List<Rank> orderedRanks() {
		return Arrays.asList(Rank.values());
	}

}
