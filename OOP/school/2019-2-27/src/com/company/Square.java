package com.company;

public class Square extends UnaryOperation {



    public Square(Calculator calculator) {
        super("^2", calculator);
    }

    @Override
    public double calculate(double value) {
        return Math.pow(value, 2);
    }
}
