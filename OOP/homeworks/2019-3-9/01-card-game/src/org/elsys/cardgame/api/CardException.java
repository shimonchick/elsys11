package org.elsys.cardgame.api;

public class CardException extends RuntimeException{


    /**
     *
     */
    private static final long serialVersionUID = 8822513014262189134L;

    @Override
    public String getMessage() {
        return message;
    }

    private final String message;

    public CardException(String message) {
        this.message = message;
    }
}
