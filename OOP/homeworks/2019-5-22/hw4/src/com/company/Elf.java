package com.company;

import java.util.concurrent.BrokenBarrierException;

public class Elf implements Runnable {
    private int id;
    private final int LAST_ELF = 0;

    public Elf(int id) {
        this.id = id;
    }

    @Override
    public void run() {
        for(int i = 0; i < 10; i++) {
            try {
                Main.elfSem.acquire();
                System.out.println("elfSem acquired");
                int elf;
                elf = Main.elfBarrier.await();
                if (elf == LAST_ELF) {
                    Main.santaSem.acquire();
                    System.out.println("santaSem acquired");
                }
                Thread.sleep(200);
                System.out.println("Elf " + id + "got help from santaSem");
                if (elf == LAST_ELF) {
                    Main.santaSem.release();
                    System.out.println("santa semaphore released");
                }

                Main.elfSem.release();
                System.out.println("elf semaphore released");
            } catch (InterruptedException | BrokenBarrierException e) {
                e.printStackTrace();
            }
        }
    }
}
