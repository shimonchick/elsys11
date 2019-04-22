package com.company;

public class Main {

    public static void main(String[] args) {
//        System.out.println(IntegrationService.integrateLn(5, 10, 10));
        double result1 = new AbstractIntegrable() {
            @Override
            double calculate(double x) {
                return Math.log(x);
            }
        }.integrate(2, 3, 1000);

        double result2 = AbstractIntegrable.integrate(new MathFunction() {
            @Override
            public double calculate(double x) {
               return Math.log(x);
            }
        },
                2,
                3,
                1000);

        double result3 = AbstractIntegrable.integrate(Math::log, 2, 3, 1000);
        System.out.println(result1);
        System.out.println(result2);
        System.out.println(result3);
    }
}
