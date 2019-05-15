package com.company;

import java.util.stream.IntStream;

public class CounterExample {
    public static long counter = 0L;
    private static Object lock = new Object();

    public static void main(String[] args) {
        Thread[] threads = new Thread[100];
        for(int i =0; i < 100; i++){
            threads[i] = new Thread(() -> {
                for(int j = 0; j < 10000; j++){
                    synchronized (CounterExample.class){
                        counter ++;
                    }
                }
                decrement(10);
            });
            threads[i].start();
        }
        for(Thread t: threads){
            try {
                t.join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
        System.out.println("exit of main, counter =" + counter);
    }

    private static synchronized void decrement(int i) {
        counter -= i;
    }
}
