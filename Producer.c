#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int in = 0, out = 0;

// 3 Semaphores
sem_t mutex;   // for mutual exclusion
sem_t empty;   // counts empty slots
sem_t full;    // counts filled slots

// Producer Thread
void* producer(void* arg) {
    int item;

    for(int i = 0; i < 10; i++) {
        item = rand() % 100;

        sem_wait(&empty);   // wait if buffer is full
        sem_wait(&mutex);   // lock critical section

        buffer[in] = item;
        printf("Produced: %d at index %d\n", item, in);
        in = (in + 1) % BUFFER_SIZE;

        sem_post(&mutex);   // unlock
        sem_post(&full);    // increase filled slots

        sleep(1);
    }
    return NULL;
}

// Consumer Thread
void* consumer(void* arg) {
    int item;

    for(int i = 0; i < 10; i++) {

        sem_wait(&full);    // wait if buffer is empty
        sem_wait(&mutex);   // lock critical section

        item = buffer[out];
        printf("Consumed: %d from index %d\n", item, out);
        out = (out + 1) % BUFFER_SIZE;

        sem_post(&mutex);   // unlock
        sem_post(&empty);   // increase empty slots

        sleep(2);
    }
    return NULL;
}

int main() {
    pthread_t p, c;

    // Initialize semaphores
    sem_init(&mutex, 0, 1);           // binary semaphore
    sem_init(&empty, 0, BUFFER_SIZE); // initially all slots empty
    sem_init(&full, 0, 0);            // initially no items

    // Create threads
    pthread_create(&p, NULL, producer, NULL);
    pthread_create(&c, NULL, consumer, NULL);

    // Wait for threads to finish
    pthread_join(p, NULL);
    pthread_join(c, NULL);

    // Destroy semaphores
    sem_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
}