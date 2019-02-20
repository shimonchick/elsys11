package com.company;

public class Member {

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public Member(String name, double subscription) {
        this.name = name;
        this.subscription = subscription;
    }

    public double getSubscription() {
        return subscription;
    }

    public void setSubscription(double subscription) {
        this.subscription = subscription;
    }

    private String name;

    private double subscription;
}
