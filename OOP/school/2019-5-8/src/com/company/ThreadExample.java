package com.company;

public class ThreadExample extends Thread {

    @Override
    public void run(){
        System.out.println("hello from thread before sleep");
        try{
            Thread.sleep(2000);
        }catch (InterruptedException e){
            e.printStackTrace();
        }
        System.out.println("woke up");
    }

    public static void main(String[] args) {
        Thread[] threads = new Thread[10];
        for( Thread t : threads){
            t = new ThreadExample();
            t.start();
        }
        for( Thread t : threads){
            try {
                t.join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
        System.out.println("end of main");
    }

}
