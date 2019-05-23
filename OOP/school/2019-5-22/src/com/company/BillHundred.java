package com.company;

public class BillHundred extends Bill  implements Comparable<Bill> {

    public int something;
    public BillHundred() {
    }

    public BillHundred(Integer value) {
        super(value);
    }
}
