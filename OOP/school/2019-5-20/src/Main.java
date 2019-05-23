import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.IntStream;

public class Main {
    public static void main(String[] args) {
        String[] names = {"Socrates", "Plato", "Aristotle", "Confucius"};

        List<Fork> forks = IntStream.range(0, names.length)
                .mapToObj(Fork::new)
                .collect(Collectors.toList());

        List<Thread> threads = IntStream
                .range(0, names.length)
                .mapToObj(i -> new Philosopher(names[i], forks.get(i), forks.get((i + 1) % forks.size())))
                .map(Thread::new)
                .peek(Thread::start)
                .collect(Collectors.toList());

        for(Thread t: threads ){
            try {
                t.join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }


    }
}
