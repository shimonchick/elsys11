package com.company;

import java.util.ArrayList;
import java.util.List;

public abstract class BaseGate implements Gate{

    private List<Wire> inputs = new ArrayList<>();
    private List<Wire> outputs = new ArrayList<>();

    public void addInput(Wire wire){
        if(!inputs.contains(wire)){
            inputs.add(wire);
            wire.connect(this);
        }
    }

    public void addOutput(Wire wire){
        if(!outputs.contains(wire)){
            outputs.add(wire);
            //wire.connect(this);
        }
    }
}
