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
    public Member(String name, double subscription, Rank rank) {
        this.name = name;
        this.subscription = subscription;
        this.rank = rank;
    }


    public double getSubscription() {
        return subscription;
    }

    public void setSubscription(double subscription) {
        this.subscription = subscription;
    }

    private String name;

    private double subscription;

    private Rank rank;

    public Rank getRank() {
        return rank;
    }

    public void setRank(Rank rank) {
        this.rank = rank;
    }
}
