package org.elsys.cardgame.implementation;

import org.elsys.cardgame.api.*;

import java.util.LinkedList;
import java.util.List;

public class WarGame implements Game {

    Deck deck;
    Hand hand;
    List<Operation> operations;
    private DealOperation dealOperation;

    public WarGame(List<Card> cards) {
        this.deck = new WarDeck(cards);
        //System.out.println("Deck cards after initialization");
        //System.out.println(this.deck.getCards().toString());
        //this.hand = new HandClass(cards);
        this.operations = new LinkedList<>();
        this.initializeOperations();

    }

    private void initializeOperations() {
        this.addOperation(new SizeOperation("size", this.deck));
        this.addOperation(new DrawBottomCardOperation("draw_bottom_card", this.deck));
        this.addOperation(new DrawTopCardOperation("draw_top_card", this.deck));
        this.addOperation(new TopCardOperation("top_card", this.deck));
        this.addOperation(new BottomCardOperation("bottom_card", this.deck));
        this.addOperation(new ShuffleOperation("shuffle", this.deck));
        this.addOperation(new SortOperation("sort", this.deck));
        this.dealOperation = new DealOperation("deal", this.deck, this.hand);
        this.addOperation(this.dealOperation);

    }


    @Override
    public Deck getDeck() {
        System.out.println("Returned deck cards");
        System.out.println(this.deck.getCards().toString());
        return this.deck;
    }

    @Override
    public Hand getDealtHand() {
        System.out.println("Dealt hand:");
        System.out.println(this.dealOperation.getHand().getCards().toString());
        System.out.println("Remaining cards");
        System.out.println(this.deck.getCards().toString());
        return this.dealOperation.getHand();
    }

    @Override
    public void setDealtHand(Hand hand) {
        this.hand = hand;
    }

    @Override
    public void process(String command) {
        for(Operation op : operations){
            if(command.equals(op.getName())){
                op.execute();
            }
        }
    }

    @Override
    public void addOperation(Operation operation) {
        this.operations.add(operation);
    }
}
