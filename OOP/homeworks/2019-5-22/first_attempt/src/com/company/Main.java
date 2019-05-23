package com.company;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.CyclicBarrier;
import java.util.concurrent.Semaphore;
import java.util.concurrent.locks.ReentrantLock;
import java.util.stream.Collectors;
import java.util.stream.IntStream;

public class Main {

//    private static final int BARRIER_REINDEER_COUNT = 9;
//    private static final int BARRIER_ELF_COUNT = 3;


    public static int elfCounter = 0;
    public static int reindeerCounter = 0;

    public static ReentrantLock countersLock;
    public static ReentrantLock elfLock;
    public static Semaphore santaSem;
    public static Semaphore reindeerSem;
    public static Semaphore elfSem;

//    public static CyclicBarrier elfBarrier;
//    public static CyclicBarrier reindeerBarrier;


    public static void main(String[] args) {

        // TODO: initialize semaphores

        List<Thread> reindeerThreads = IntStream.of(9)
                .mapToObj(value -> new Reindeer())
                .map(Thread::new)
                .peek(Thread::start)
                .collect(Collectors.toList());

        List<Thread> elfThreads = IntStream.of(10)
                .mapToObj(value -> new Elf())
                .map(Thread::new)
                .peek(Thread::start)
                .collect(Collectors.toList());
        Thread santaThread = new Thread(new Santa());
        santaThread.start();

        try {
            santaThread.join();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        for(Thread t: reindeerThreads){
            try {
                t.join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
        for(Thread t : elfThreads){
            try {
                t.join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
        System.out.println("Santa thread ");
        //        reindeerBarrier = new CyclicBarrier(BARRIER_REINDEER_COUNT, ()->{
//            System.out.println("9 reindeer are going to wake santa");
//        });
//        elfBarrier = new CyclicBarrier(BARRIER_ELF_COUNT, ()->{
//            System.out.println("3 elfs are going to wake santa");
//        });

    }
}
