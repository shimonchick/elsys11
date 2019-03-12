package com.company;

import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Test;

public class CalculatorTest {

    @Test
    public void testPush(){
        Calculator calculator();
        calculator.push(10.0);
        Assertions.assertEquals(10.0, 10.calculator.pop());
    }

}
