import java.util.concurrent.Semaphore;

class DiningPhilosophers {

    // Semaphores representing each of the 5 forks
    private final Semaphore[] forks;
    // Semaphore to limit the number of philosophers concurrently trying to eat
    private final Semaphore bouncer;

    public DiningPhilosophers() {
        forks = new Semaphore[5];
        for (int i = 0; i < 5; i++) {
            forks[i] = new Semaphore(1); // 1 permit per fork
        }
        bouncer = new Semaphore(4); // Limit concurrency to 4 philosophers
    }

    // call the run() method of any runnable to execute its code
    public void wantsToEat(int philosopher,
                           Runnable pickLeftFork,
                           Runnable pickRightFork,
                           Runnable eat,
                           Runnable putLeftFork,
                           Runnable putRightFork) throws InterruptedException {
        
        int leftFork = philosopher;
        int rightFork = (philosopher + 1) % 5;

        // 1. Ask permission to enter the dining area
        bouncer.acquire();

        // 2. Acquire locks for both forks
        forks[leftFork].acquire();
        forks[rightFork].acquire();

        // 3. Execute actions
        pickLeftFork.run();
        pickRightFork.run();
        eat.run();
        putLeftFork.run();
        putRightFork.run();

        // 4. Release locks for both forks
        forks[leftFork].release();
        forks[rightFork].release();

        // 5. Leave the dining area
        bouncer.release();
    }
}
