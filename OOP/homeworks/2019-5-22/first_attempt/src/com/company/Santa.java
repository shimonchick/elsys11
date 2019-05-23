package com.company;

public class Santa implements Runnable {

    @Override
    public void run() {
        while(true){
            try {
                wait();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            Main.countersLock.lock();

            if(Main.reindeerCounter == 9){
                Main.reindeerCounter = 0;
                prepSleigh();
                Main.reindeerSem.notify();
            }
            else{
                for(int i = 0; i < 3; i++){
                    Main.elfSem.notify();
                    helpElves();
                }
            }
            Main.countersLock.unlock();

        }
    }

    private void helpElves() {
        System.out.println("Santa is helping the elves");
    }

    private void prepSleigh() {
        System.out.println("Santa prepared the sleigh");
    }
}
