package com.company;

import java.util.ArrayList;
import java.util.List;

public class Wire {
    private boolean state = false;
    List<Gate> gates = new ArrayList<>();

    public Wire(boolean state, List<Gate> gates) {
        this.state = state;
        this.gates = gates;

    }


    public Wire() {
    }

    public boolean getState() {
        return state;
    }

    public void setState(boolean state) {
        this.state = state;
        for(Gate g: gates){
            g.act();
        }
    }
    public void connect(Gate gate){
        if(!gates.contains(gate)){
            gates.add(gate);
        }
    }
}
