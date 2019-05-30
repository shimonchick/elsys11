package org.elsys.water;

import java.util.Random;
import java.util.concurrent.CyclicBarrier;
import java.util.concurrent.Semaphore;
import java.util.concurrent.atomic.AtomicBoolean;
import java.util.concurrent.locks.ReentrantLock;

public class WaterConstructor {

	private CyclicBarrier moleculeBarrier = new CyclicBarrier(3);

	private Semaphore oxygenSemaphore = new Semaphore(1);
	private Semaphore hydrogenSemaphore = new Semaphore(2);

	public void proceedOxygen(Oxygen oxygen) throws Exception {
		// TODO: implement me

		oxygenSemaphore.acquire();

		moleculeBarrier.await();

		oxygen.bond();

		moleculeBarrier.await();

		oxygenSemaphore.release();


	}

	public void proceedHydrogen(Hydrogen hydrogen) throws Exception {

		hydrogenSemaphore.acquire();

		moleculeBarrier.await();

		hydrogen.bond();

		moleculeBarrier.await();

		hydrogenSemaphore.release();


	}

	public static void main(String[] args) {
		WaterConstructor constructor = new WaterConstructor();
		Random random = new Random();
		int oxygen = 0;
		int hydrogen = 0;

		while (true) {
			if (random.nextInt(3) == 0) {
				Oxygen o = new Oxygen(++oxygen, constructor);
				new Thread(o).start();
			} else {
				Hydrogen h = new Hydrogen(++hydrogen, constructor);
				new Thread(h).start();
			}
			try {
				Thread.sleep(random.nextInt(1000));
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}
	}
}
