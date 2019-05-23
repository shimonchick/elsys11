public class Philosopher implements Runnable{


    private final String name;

    Fork left, right;
    public Philosopher(String name, Fork left, Fork right) {
        this.name = name;
        this.left = left;
        this.right = right;
    }

    public Philosopher(String name) {
        this.name = name;
    }


    public void think(){
        System.out.printf("%s is thinking\n", name);
        try {
            Thread.sleep(1000);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
    public void eat(){
        System.out.printf("%s is hungry\n", name);
        left.get();
        right.get();

        left.put();
        right.put();

    }

    @Override
    public void run() {
        while(true){
            think();
            eat();
            sleep();
        }
    }

    private void sleep() {
    }
}
