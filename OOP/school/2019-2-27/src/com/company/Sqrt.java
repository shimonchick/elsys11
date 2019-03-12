package com.company;

public class Sqrt extends UnaryOperation{
    public Sqrt(Calculator calculator) {
        super("sqrt", calculator);
    }

    @Override
    public double calculate(double value) {
        return Math.sqrt(value);
    }
}
