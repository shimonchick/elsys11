package com.company;

import java.util.Objects;

public class Member {
    private long id;
    private int rank;
    private String name;

    public Member(long id, int rank, String name) {
        this.id = id;
        this.rank = rank;
        this.name = name;
    }

    @Override
    public String toString() {
        return "Member{" +
                "id=" + id +
                ", rank=" + rank +
                ", name='" + name + '\'' +
                '}';
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof Member)) return false;
        Member member = (Member) o;
        return getId() == member.getId() &&
                getRank() == member.getRank() &&
                Objects.equals(getName(), member.getName());
    }

    @Override
    public int hashCode() {
        return Objects.hash(getId(), getRank(), getName());
    }

    public long getId() {
        return id;
    }

    public void setId(long id) {
        this.id = id;
    }

    public int getRank() {
        return rank;
    }

    public void setRank(int rank) {
        this.rank = rank;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }
}
