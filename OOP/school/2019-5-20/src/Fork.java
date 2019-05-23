import java.util.concurrent.locks.ReentrantLock;

public class Fork {

    private ReentrantLock lock;

    public Fork(int i) {
    }

    public void get(){

        lock.lock();

    }
    public void put(){

        lock.unlock();
    }

}
