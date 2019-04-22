package com.company;

public  abstract class AbstractIntegrable {

    abstract double calculate(double x);

    public double integrate(double from, double to, int steps){
        double stepSize = (to - from) / steps;
        double result = 0;
        for(double x = from; x < to; x += stepSize){
            result += Math.abs(calculate(x) * stepSize);

        }
        return result;
    }

    public static double integrate(MathFunction func, double from, double to, int steps){
        double stepSize = (to - from) / steps;
        double result = 0;
        for(double x = from; x < to; x += stepSize){
            result += Math.abs(func.calculate(x) * stepSize);

        }
        return result;
    }

}
