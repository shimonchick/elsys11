package com.company;

import java.util.concurrent.BrokenBarrierException;
import java.util.function.IntFunction;

public class Reindeer implements Runnable {

    @Override
    public void run() {
        Main.countersLock.lock();

        Main.reindeerCounter++;
        int MAX_REINDEER_TO_AWAKE_SANTA = 9;
        if (Main.reindeerCounter == MAX_REINDEER_TO_AWAKE_SANTA) {
            Main.santaSem.notify();
        }

        Main.countersLock.unlock();

        try {
            Main.reindeerSem.wait();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        getHitched();
    }

    private void getHitched() {
        System.out.println("Reindeer got hitched to the sleigh");
    }
}
