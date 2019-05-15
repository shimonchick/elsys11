package com.company;

public class DeadlockExample {
    public static long counter = 0L;
    public static long counter2 = 0L;
    private static Object lock1 = new Object();
    private static Object lock2 = new Object();

    public static void main(String[] args) {
        Thread[] threads = new Thread[2];
        threads[0] = new Thread(() -> {
            for(int j = 0; j < 1000; j ++){
                synchronized (lock1){
                    counter++;

                }
            }
        });
        for(Thread t: threads){
            try {
                t.join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
        System.out.println("exit of main, counter =" + counter);
    }

}
