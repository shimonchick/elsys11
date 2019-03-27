package com.company;

public class InverterGate extends BaseGate {
    private Wire input;
    private Wire output;

    public InverterGate(Wire input, Wire output) {
        this.input = input;
        this.output = output;
        addInput(input);
        addOutput(output);
    }

    @Override
    public void act() {
        output.setState(!input.getState());
    }
}
