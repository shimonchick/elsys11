package com.company;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.CyclicBarrier;
import java.util.concurrent.Semaphore;
import java.util.concurrent.locks.ReentrantLock;
import java.util.stream.Collectors;
import java.util.stream.IntStream;

public class Main {


    private static final int MAX_REINDEER_COUNT = 9;
    private static final int MAX_ELF_COUNT= 10;
    private static final int MAX_ELF_COUNT_TO_SANTA = 3;

    static Semaphore santaSem = new Semaphore(1, true);
    static Semaphore elfSem = new Semaphore(MAX_ELF_COUNT_TO_SANTA, true);

    static CyclicBarrier reindeerBarrier = new CyclicBarrier(MAX_REINDEER_COUNT, ()-> System.out.println("Awaited all reindeer"));
    static CyclicBarrier sleigh = new CyclicBarrier(MAX_REINDEER_COUNT, ()-> System.out.println("Awaited reindeer in sleigh"));
    static CyclicBarrier elfBarrier = new CyclicBarrier(MAX_ELF_COUNT_TO_SANTA, ()-> System.out.println("Awaited all elves"));


    public static void main(String[] args) {
        List<Thread> reindeerThreads = new ArrayList<>();
        List<Thread> elfThreads = new ArrayList<>();
        for (int i = 0; i < MAX_REINDEER_COUNT; i++) {
            reindeerThreads.add(new Thread(new Reindeer(i)));
        }
        System.out.println("reindeer thread count: " + reindeerThreads.size());
        for(int i = 0; i < MAX_ELF_COUNT; i++){
            elfThreads.add(new Thread(new Elf(i)));
        }
        System.out.println("elf thread count: " + elfThreads.size());
        for (Thread reindeerThread : reindeerThreads) {
            reindeerThread.start();
        }
        for (Thread elfThread : elfThreads) {
            elfThread.start();
        }
        for (Thread reindeerThread : reindeerThreads) {
            try {
                reindeerThread.join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
        System.out.println("reindeer threads joined");
        for (Thread elfThread : elfThreads) {
            try {
                elfThread.join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }

        System.out.println("Program finished execution");

    }


}
