package com.company;

public class Elf implements Runnable {
    @Override
    public void run() {
        Main.elfLock.lock();

        Main.countersLock.lock();

        Main.elfCounter++;
        if(Main.elfCounter == 3){
            Main.santaSem.notify();
        }
        else{
            Main.elfLock.unlock();
        }

        Main.countersLock.unlock();

        try {
            Main.elfSem.wait();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        getHelp();
        Main.elfLock.lock();

        Main.elfCounter--;
        if(Main.elfCounter == 0){
            Main.elfLock.unlock();
        }

        Main.elfLock.unlock();
    }

    private void getHelp() {
        System.out.println("Elf is getting help from santa");
    }
}
