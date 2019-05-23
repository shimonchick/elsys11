package com.company;

public class Bill implements Comparable<Bill> {

    private Integer value;


    public Bill() {
        this.value = 1;
    }

    public Bill(Integer value) {
        this.value = value;
    }

    public Integer getValue() {
        return value;
    }

    public void setValue(Integer value) {
        this.value = value;
    }


    @Override
    public int compareTo(Bill o) {
        return this.getValue() - o.getValue();
    }

}
