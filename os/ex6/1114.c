#include <semaphore.h>
#include <stdlib.h>

typedef struct {
    // Two semaphores to control execution flow
    sem_t sem_second;
    sem_t sem_third;
} Foo;

Foo* fooCreate() {
    Foo* obj = (Foo*) malloc(sizeof(Foo));
    
    // Initialize both semaphores with a value of 0.
    // This forces any thread calling sem_wait to block immediately.
    sem_init(&(obj->sem_second), 0, 0);
    sem_init(&(obj->sem_third), 0, 0);
    
    return obj;
}

void first(Foo* obj) {
    // printFirst() outputs "first". Do not change or remove this line.
    printFirst();
    
    // Unblock the second thread
    sem_post(&(obj->sem_second));
}

void second(Foo* obj) {
    // Wait until the first thread posts to sem_second
    sem_wait(&(obj->sem_second));
    
    // printSecond() outputs "second". Do not change or remove this line.
    printSecond();
    
    // Unblock the third thread
    sem_post(&(obj->sem_third));
}

void third(Foo* obj) {
    // Wait until the second thread posts to sem_third
    sem_wait(&(obj->sem_third));
    
    // printThird() outputs "third". Do not change or remove this line.
    printThird();
}

void fooFree(Foo* obj) {
    // Clean up resources from memory
    sem_destroy(&(obj->sem_second));
    sem_destroy(&(obj->sem_third));
    free(obj);
}
