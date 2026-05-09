#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5

sem_t chopstick[N];

void *philosopher(void *num) {
    int id = *(int *)num;

    while (1) {
        printf("Philosopher %d is THINKING\n", id);
        sleep(1);


        if (id == N - 1) {
            sem_wait(&chopstick[(id + 1) % N]);
            sem_wait(&chopstick[id]);
        } else {
            sem_wait(&chopstick[id]);
            sem_wait(&chopstick[(id + 1) % N]);
        }

        printf("Philosopher %d is EATING\n", id);
        sleep(2);


        sem_post(&chopstick[id]);
        sem_post(&chopstick[(id + 1) % N]);

        printf("Philosopher %d finished EATING\n", id);
        sleep(1);
    }
}

int main() {
    pthread_t tid[N];
    int phil[N];


    for (int i = 0; i < N; i++) {
        sem_init(&chopstick[i], 0, 1);
        phil[i] = i;
    }


    for (int i = 0; i < N; i++) {
        pthread_create(&tid[i], NULL, philosopher, &phil[i]);
    }


    for (int i = 0; i < N; i++) {
        pthread_join(tid[i], NULL);
    }

    return 0;
}
