package com.company;

import org.junit.Before;
import org.junit.Test;

import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertTrue;

public class TestAndGate {
    private Wire in1;
    private Wire in2;
    private Wire out;
    private Gate gate;

    @Before
    public void setup(){
        in1 = new Wire();
        in2 = new Wire();
        out = new Wire();

        gate = new AndGate(in1, in2, out);
    }

    @Test
    public void testActIn1FalseIn2False(){
        in1.setState(false);
        in2.setState(false);
        assertFalse(out.getState());
    }
    @Test
    public void testActIn1FalseIn2True(){
        in1.setState(false);
        in2.setState(true);
        assertFalse(out.getState());
    }
    @Test
    public void testActIn1TrueIn2False(){
        in1.setState(true);
        in2.setState(false);
        assertFalse(out.getState());
    }

    @Test
    public void testActIn1TrueIn2True(){
        in1.setState(true);
        in2.setState(true);
        assertTrue(out.getState());
    }


}
