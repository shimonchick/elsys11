package com.company;

public abstract class UnaryOperation extends BaseOperation {
    @Override
    public void execute() {
        double value = getCalculator().pop();
        value = calculate(value);
        getCalculator().push(value);
    }

    public abstract double calculate(double value);

    public UnaryOperation(String name, Calculator calculator) {
        super(name, calculator);
    }
}
