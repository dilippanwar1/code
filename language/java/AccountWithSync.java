import java.util.concurrent.*;
import java.util.concurrent.locks.*;

public class AccountWithSync {
    private static Account account = new Account();

    public static void main(String[] args) {
	ExecutorService executor = Executors.newFixedThreadPool(100);
	
	executor.execute(new DepositTask());
	executor.execute(new WithdrawTask());

	executor.shutdown();

	while (!executor.isTerminated());
	System.out.println("What's the balance? " + account.getBalance());
    }




    public static class DepositTask implements Runnable {
	public void run() {
	    try {
		while (true) {
		    account.deposit(1);
		    Thread.sleep(1);
		}
	    } catch (InterruptedException e) {
	    }
	}
    }

    public static class WithdrawTask implements Runnable {
	public void run() {
	    while (true) {
		account.withdraw(3);
	    }
	}
    }
    
    public static class Account {
	private static Lock lock = new ReentrantLock();
	private static Condition newDeposit = lock.newCondition();
	private int balance;

	public int getBalance() {
	    return balance;
	}

	public void withdraw(int amount) {
	    lock.lock();
	    try {
		while (balance < amount) {
		    System.out.println("Balance is not enough");
		    newDeposit.await();
		}
		balance -= amount;
		System.out.println("Withdraw " + amount);
	    } catch (InterruptedException e) {
	    } finally {
		lock.unlock();
	    }
	}

	public void deposit(int amount) {
	    lock.lock();

	    balance += amount;
	    System.out.println("Increase balance");
	    newDeposit.signalAll();
	    
	    lock.unlock();
	}
    }
}
