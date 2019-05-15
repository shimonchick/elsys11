package com.company;

import java.util.LinkedList;
import java.util.Queue;

public final class BlockingQueue<E> {


    private LinkedList<E> values = new LinkedList<>();
    private final int size;

    public BlockingQueue(int size) {
        this.size = size;
    }

    public synchronized void push(E value) {
        while (values.size() >= size) {
            try {
                wait();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
        values.add(value);

        notifyAll();
    }

    public synchronized E pop() {

        while (values.isEmpty()) {
            try {
                wait();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
        notifyAll();
        return values.pop();

    }

}
