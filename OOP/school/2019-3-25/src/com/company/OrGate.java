package com.company;

public class OrGate extends BinaryGate{
    public OrGate(Wire in1, Wire in2, Wire out) {
        super(in1, in2, out);
    }

    @Override
    public void act() {
        getOut().setState(
                getIn1().getState()
                || getIn2().getState()
        );
    }
}
