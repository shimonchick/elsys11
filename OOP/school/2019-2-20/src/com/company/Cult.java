package com.company;


import java.util.*;

public class Cult {


    private Member leader;
    private String name;

    public Member getLeader() {
        return leader;
    }

    public void setLeader(Member leader) {
        this.leader = leader;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof Cult)) return false;
        Cult cult = (Cult) o;
        return Objects.equals(getLeader(), cult.getLeader()) &&
                Objects.equals(getName(), cult.getName()) &&
                Objects.equals(getMembers(), cult.getMembers());
    }

    @Override
    public int hashCode() {
        return Objects.hash(getLeader(), getName(), getMembers());
    }



    public Cult(Member leader, String name, List<Member> members) {
        this.leader = leader;
        this.name = name;
        this.members = members;
    }

    public List<Member> getMembers() {
        return members;
    }

    public void setMembers(List<Member> members) {
        this.members = members;
    }

    private List<Member> members;

    public List<Member> getMembersOrderBySubscription(){
        ArrayList<Member> result = new ArrayList<>(members);
        result.sort(new Comparator<Member>() {
            @Override
            public int compare(Member o1, Member o2) {
                if(o1.getSubscription() > o2.getSubscription()){
                    return -1;
                }
                else if(o1.getSubscription() < o2.getSubscription()){
                    return 1;
                }
                else{
                    return 0;
                }
            }
        });
        return result;

    }
    //TODO:  implement enum of ranks and order members by rank. Make unit tests for this function
    public Map<String, List<Member>> getMemberByRank(){
        Map<String, List<Member>> ranking = new HashMap<String,List<Member>>();
        Set<Rank> ranks = new HashSet<Rank>();
        for (Member m: getMembers()) {
            ranks.add(m.getRank());
        }
        ranks.toArray().sort(new Comparator<Rank>() {
            @Override
            public int compare(Rank o1, Rank o2) {
                if(o1.getValue() > o2.getValue()){
                    return 1;
                }
                else if(o1.getValue() < o2.getValue()){
                    return -1;
                }
                else{
                    return 0;
                }
            }
        });
        for(Rank r : ranks){
            List<Member> membersOfRank = new LinkedList<Member>();
            for (Member m: getMembers()) {
                if(m.getRank().equals(r)){
                    membersOfRank.add(m);
                }
            }
            ranking.put(r.getName(), membersOfRank);
        }
        return ranking;

    }

}
