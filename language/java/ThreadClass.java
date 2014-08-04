public class ThreadClass implements Runnable {
    private char charToPrint;
    private int time;

    public ThreadClass(char ch, int t) {
	charToPrint = ch;
	time = t;
    }

    public void run() {
	for (int i = 0; i < time; i++) {
	    System.out.print(charToPrint);
	    try {
		Thread.sleep(1);
	    } catch (InterruptedException e) {
	    }
	}
    }
}
