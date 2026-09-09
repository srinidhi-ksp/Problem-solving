#include <semaphore.h>
#include <pthread.h>
#include <stdlib.h>

typedef struct {
    sem_t h_sem;       // Controls hydrogen thread throughput
    sem_t o_sem;       // Controls oxygen thread throughput
    pthread_mutex_t lock; // Protects the hydrogen counter
    int h_count;       // Tracks how many H's have been released in the current batch
} H2O;

H2O* h2oCreate() {
    H2O* obj = (H2O*) malloc(sizeof(H2O));
    
    // Allow 2 Hydrogen threads to pass at a time
    sem_init(&(obj->h_sem), 0, 2);
    // Keep Oxygen threads blocked initially
    sem_init(&(obj->o_sem), 0, 0);
    // Initialize mutex lock
    pthread_mutex_init(&(obj->lock), NULL);
    
    obj->h_count = 0;
    
    return obj;
}

void hydrogen(H2O* obj) {
    // Wait for an available hydrogen slot
    sem_wait(&(obj->h_sem));
    
    // releaseHydrogen() outputs "H". Do not change or remove this line.
    releaseHydrogen();
    
    pthread_mutex_lock(&(obj->lock));
    obj->h_count++;
    
    // Once 2 Hydrogen threads have finished, release 1 Oxygen thread
    if (obj->h_count == 2) {
        sem_post(&(obj->o_sem));
    }
    pthread_mutex_unlock(&(obj->lock));
}

void oxygen(H2O* obj) {
    // Wait until 2 Hydrogen threads signal that they are ready
    sem_wait(&(obj->o_sem));
    
    // releaseOxygen() outputs "O". Do not change or remove this line.
    releaseOxygen();
    
    pthread_mutex_lock(&(obj->lock));
    // Reset the hydrogen counter for the next molecule batch
    obj->h_count = 0;
    pthread_mutex_unlock(&(obj->lock));
    
    // Release 2 new slots for the next pair of Hydrogen threads
    sem_post(&(obj->h_sem));
    sem_post(&(obj->h_sem));
}

void h2oFree(H2O* obj) {
    // Clean up system semaphores and mutex locks
    sem_destroy(&(obj->h_sem));
    sem_destroy(&(obj->o_sem));
    pthread_mutex_destroy(&(obj->lock));
    free(obj);
}
