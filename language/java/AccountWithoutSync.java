import java.util.concurrent.*;

public class AccountWithoutSync {
    private static Account account = new Account();

    public static void main(String[] args) {
	ExecutorService executor = Executors.newFixedThreadPool(100);
	
	for (int i = 0; i < 100; i++) {
	    executor.execute(new AddAPennyTask());
	}

	executor.shutdown();

	while (!executor.isTerminated());
	System.out.println("What's the balance? " + account.getBalance());
    }




    public static class AddAPennyTask implements Runnable {
	public void run() {
	    account.deposit(1);
	}
    }
     
    public static class Account {
	private int balance;

	public int getBalance() {
	    return balance;
	}

	public synchronized void deposit(int amount) {
	    int newBalance = balance + amount;

	    try {
		Thread.sleep(10);
	    } catch (InterruptedException e) {
	    }

	    balance = newBalance;
	}
    }
}
