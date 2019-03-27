package com.company;

public abstract class BinaryGate extends BaseGate {
    private Wire in1;
    private Wire in2;
    private Wire out;

    public BinaryGate(Wire in1, Wire in2, Wire out) {
        this.in1 = in1;
        this.in2 = in2;
        this.out = out;
        addInput(in1);
        addInput(in2);
        addOutput(out);
    }

    public Wire getIn1() {
        return in1;
    }

    public Wire getIn2() {
        return in2;
    }

    public Wire getOut() {
        return out;
    }

}
