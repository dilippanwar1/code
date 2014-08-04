import java.util.*;
import java.util.concurrent.*;

public class Test1 extends Thread {
    private int tick = 1;
    private int num;

    public Test1(int num) {
	this.num = num;
    }

    public void run() {
	while (tick < 400000) {
	    tick++;
	    if ((tick % 50000) == 0)
		System.out.println("Thread #" + num + ", tick = " + tick);
	}
    }

    public static void main(String[] args) {
	Test1 t1 = new Test1(1);
	Test1 t2 = new Test1(2);
	Test1 t3 = new Test1(3);
	Test1 t4 = new Test1(4);

	t1.setPriority(10);
	t2.setPriority(9);
	t3.setPriority(8);
	t4.setPriority(7);

	t1.start();
	t2.start();
 	t3.start();
	t4.start();
	// t1.run();
	// t2.run();
	// t3.run();
	// t4.run();

	TreeSet<Double> mySet = new TreeSet<Double>();
	mySet.add(new Double(1.0));
	Double d = mySet.first();
	System.out.println(d);
    }
}
