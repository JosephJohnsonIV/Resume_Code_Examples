/*
 * Joseph Johnson IV
 * Course: CNT 4714 - Enterprise Programming Spring 2016
 * Assignment title: Project 2 � Synchronized, Cooperating Threads Under Locking
 * Program to simulate a single bank account being deposited to, and withdrawn from, by multiple threads.
 */

import java.util.Random;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class BankAccount
{
	// Declaring necessary variables
	private int balance;
	private Lock access;
	private Condition funds;

	public BankAccount()
	{
		balance = 0;
		access = new ReentrantLock();		// Reentrant lock to synchronize account access
		funds = access.newCondition();		// Declaring a condition for the threads to block on
	}

	// Method to withdraw from the account
	public void withdraw(int id, int amount)
	{
		access.lock();						// Need to lock before performing the withdraw

		if (balance - amount >= 0)			// Make sure there's enough money in the account
		{
			balance = balance - amount;

			System.out.println("				Thread " + id + " withdraws $" + amount
					+ "		Balance is $" + balance);
		}

		else
		{
			System.out.println("				Thread " + id + " withdraws $" + amount
					+ "	Withdrawal - Blocked - Insufficient Funds");

			try { funds.await(); }			// If there isn't enough money in the account, this thread must block
			catch (Exception e) { e.printStackTrace(); }
		}

		access.unlock();					// Unlock the account
	}

	// MEthod to deposit into the account
	public void deposit(int id, int amount)
	{
		access.lock();						// Lock the account
		balance = balance + amount;

		System.out.println("Thread " + id + " deposits $" + amount
				+ "						Balance is $" + balance);

		try { funds.signal(); }				// Signal threads waiting for more funds
		catch (Exception e) {e.printStackTrace(); }

		access.unlock();					// Unlock the account
	}

	// Class for the withdraw threads
	public class Withdraw extends Thread
	{
		// Some variables I will use
		private int id;
		private int value;
		private Random rand;
		private BankAccount bank;

		// Constructor for the class
		public Withdraw(int threadNum, BankAccount a)
		{
			bank = a;
			value = 0;
			id = threadNum;
			rand = new Random();
		}

		public void run()
		{
			while (true)				// Run forever
			{
				// Calculate the withdraw amount and call the method
				value = rand.nextInt(50) + 1;
				bank.withdraw(id, value);

				// Sleep the withdraw thread for a random time between 25 and 75 milliseconds
				try { Thread.sleep(rand.nextInt(100) + 50); }
				catch (Exception e) { e.printStackTrace(); }
			}
		}
	}

	// Class for the Deposit threads
	public class Deposit extends Thread
	{
		// The same variables as before
		private int id;
		private int value;
		private Random rand;
		private BankAccount bank;

		// Constructor for the account
		public Deposit(int threadNum, BankAccount a)
		{
			id = threadNum;
			value = 0;
			bank = a;
			rand = new Random();
		}

		public void run()
		{
			while (true)				// Run forever
			{
				// Calculate the deposit amount and call the deposit method
				value = rand.nextInt(200) + 1;
				bank.deposit(id, value);

				// Sleep the thread for a random time between 700 and 1400 milliseconds
				try { Thread.sleep(rand.nextInt(700) + 700); }
				catch (Exception e) { e.printStackTrace(); }
			}
		}
	}

	// Main method to run the show
	public static void main(String[] args)
	{
		// Creating the account and an array of deposit and withdraw threads
		BankAccount a = new BankAccount();
		Deposit d[] = new Deposit[3];
		Withdraw w[] = new Withdraw[6];

		ExecutorService exec = Executors.newFixedThreadPool(9);	// Executor service to launch threads

		for (int i = 0; i < 3; i++)
			d[i] = a.new Deposit(i + 1, a);

		for (int j = 0; j < 6; j++)
			w[j] = a.new Withdraw(j + 4, a);

		for (int i = 0; i < 3; i++)
			exec.execute(d[i]);

		for (int j = 0; j < 6; j++)
			exec.execute(w[j]);

		exec.shutdown();
	}
}
