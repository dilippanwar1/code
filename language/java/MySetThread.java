import java.util.*;
import java.util.concurrent.locks.*;

public class MySetThread {
    ArrayList myElements = new ArrayList();
    private static Lock lock = new ReentrantLock();
    private static Condition newVal = lock.newCondition();


    public boolean add(Object o) {
	boolean succ = false;
	lock.lock();

	try {
	    succ = myElements.add(o);
	    newVal.signalAll();
	} finally {
	    lock.unlock();
	}
	return succ;
    }

    public Object remove() {
	Object obj = null;
	lock.lock();

	try {
	    while (myElements.isEmpty() == true)
		newVal.await();

	    obj = myElements.remove(0);
	} catch (InterruptedException ex) {
	    ex.printStackTrace();
	}
	finally {
	    lock.unlock();
	}

	return obj;
    }


    public static void main(String[] args) {
	MySetThread mySetThread = new MySetThread();

	Manipulate1 man1 = new Manipulate1(mySetThread);
	Manipulate2 man2 = new Manipulate2(mySetThread);

	//	man1.run();
	man2.start();
	man1.start();
    }

}


class Manipulate1 extends Thread {
    MySetThread mySetThread;

    public Manipulate1(MySetThread mySetThread) {
	this.mySetThread = mySetThread;
    }


    public void run() {
	mySetThread.add(10);
    }
}


class Manipulate2 extends Thread {
    MySetThread mySetThread; 

    public Manipulate2(MySetThread mySetThread) {
	this.mySetThread = mySetThread;
    }


    public void run() {
	System.out.println(mySetThread.remove());
    }
}
