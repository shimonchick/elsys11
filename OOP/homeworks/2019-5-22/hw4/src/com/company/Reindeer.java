package com.company;

import java.util.concurrent.BrokenBarrierException;

public class Reindeer implements Runnable {

    private final int LAST_REINDEER = 0;

    private int id;

    public Reindeer(int id) {
        this.id = id;
    }


    @Override
    public void run() {
        for(int i = 0; i < 10; i++) {
            try {
                int reindeeer;

                reindeeer = Main.reindeerBarrier.await();

                if (reindeeer == LAST_REINDEER) {
                    Main.santaSem.acquire();
                    System.out.println("Santa's attention acquired");
                }
                Main.sleigh.await();
                System.out.println("Reindeer " + id + " Delivering toys");
                Thread.sleep(100);
                reindeeer = Main.sleigh.await(); //reindeer leaving the sleigh, we can use the same cyclic barrier
                if (reindeeer == LAST_REINDEER) {
                    Main.santaSem.release();
                    System.out.println("Santa's attention released");
                    System.out.println("All toys were delivered");
                }
            } catch (InterruptedException | BrokenBarrierException e) {
                e.printStackTrace();
            }
        }

    }
}
