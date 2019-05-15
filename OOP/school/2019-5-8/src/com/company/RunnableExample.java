package com.company;

public class RunnableExample {

    public static void main(String[] args) {
        Thread[] threads = new Thread[5];
        String[] names = {"a", "b", "c", "d", "e"};
        for(int i = 0; i < threads.length; i++){
            threads[i] = new Thread(new StudentRunnable(names[i]));
            threads[i].start();
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

class StudentRunnable implements Runnable{
    StudentRunnable(String name) {
        this.name = name;
    }

    @Override
    public void run() {
        System.out.println(name + " started something");
        try {
            Thread.sleep(1000);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        System.out.println("ready");
    }

    private final String name;

}