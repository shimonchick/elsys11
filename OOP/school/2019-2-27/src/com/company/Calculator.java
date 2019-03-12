package com.company;

import java.io.InputStream;
import java.io.PrintStream;
import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;
import java.util.Stack;

public class Calculator {
    private final Stack<Double> values;
    private final Map<String, Operation> operations;

    public void execute(String token){
        if(operations.containsKey(token)){
            Operation operation = operations.get(token);
            operation.execute();
        }
        else{
            throw new RuntimeException(
                    String.format("Operation %s not found", token)
            );
        }
    }

    public Calculator() {
        values = new Stack<Double>();
        operations = new HashMap<String, Operation>();
    }

    public Calculator(Stack<Double> values, Map<String, Operation> operations) {
        this.values = values;
        this.operations = operations;
    }

    public void addOperation(Operation operation){
        operations.put(operation.getName(), operation);
    }

    public void push(Double value){
        values.add(value);
    }

    public void run(InputStream in, PrintStream out) {
        Scanner scanner = new Scanner(in);
        while(scanner.hasNext()){
            String token = scanner.next();
            try{
                double value = Double.parseDouble(token);
                push(value);
            } catch(NumberFormatException e){
                execute(token);
                out.printf("%f\n", lastValue());
            }

        }
    }

    private Object lastValue() {
        return values.peek();
    }

    public int valuesCount(){
        return values.size();
    }
    public Double pop(){
        return values.pop();
    }
}
