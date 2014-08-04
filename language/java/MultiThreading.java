import java.util.concurrent.*;

public class MultiThreading {
    public static void main(String[] args) {
	Thread thread1 = new Thread(new ThreadClass('a', 100));
	Thread thread2 = new Thread(new ThreadClass('b', 100));

	ExecutorService executor = Executors.newFixedThreadPool(3);
	executor.execute(new ThreadClass('c', 100));
	executor.execute(new ThreadClass('d', 100));
	executor.execute(new ThreadClass('e', 100));

	executor.shutdown();
	//	thread2.setPriority(Thread.MAX_PRIORITY);
	//	thread1.start();
	//	thread2.start();
    }
}
