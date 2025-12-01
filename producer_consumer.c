//Implementation of Classical problems Producer Consumer using Threads and Semaphore.

// producer_consumer.c
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5
#define NUM_ITEMS   10   // how many items producer will produce

int buffer[BUFFER_SIZE];
int in = 0;   // index for next produced item
int out = 0;  // index for next consumed item

// Semaphores
sem_t empty;  // counts empty slots in buffer
sem_t full;   // counts filled slots in buffer
sem_t mutex;  // binary semaphore for mutual exclusion

void *producer(void *arg) {
    int i;
    for (i = 1; i <= NUM_ITEMS; i++) {
        int item = i;  // produced item

        // Wait for an empty slot
        sem_wait(&empty);
        // Enter critical section
        sem_wait(&mutex);

        // Put item in buffer
        buffer[in] = item;
        printf("Producer produced: %d at index %d\n", item, in);
        in = (in + 1) % BUFFER_SIZE;

        // Exit critical section
        sem_post(&mutex);
        // Signal that buffer has one more full slot
        sem_post(&full);

        sleep(1); // simulate time to produce
    }
    pthread_exit(NULL);
}

void *consumer(void *arg) {
    int i;
    for (i = 1; i <= NUM_ITEMS; i++) {
        int item;

        // Wait for a full slot
        sem_wait(&full);
        // Enter critical section
        sem_wait(&mutex);

        // Remove item from buffer
        item = buffer[out];
        printf("Consumer consumed: %d from index %d\n", item, out);
        out = (out + 1) % BUFFER_SIZE;

        // Exit critical section
        sem_post(&mutex);
        // Signal that buffer has one more empty slot
        sem_post(&empty);

        sleep(2); // simulate time to consume
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t prod_thread, cons_thread;

    // Initialize semaphores
    // empty = BUFFER_SIZE (all slots empty initially)
    // full = 0 (no items initially)
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    sem_init(&mutex, 0, 1);  // binary semaphore

    // Create producer and consumer threads
    if (pthread_create(&prod_thread, NULL, producer, NULL) != 0) {
        perror("Failed to create producer thread");
        exit(1);
    }
    if (pthread_create(&cons_thread, NULL, consumer, NULL) != 0) {
        perror("Failed to create consumer thread");
        exit(1);
    }

    // Wait for both threads to finish
    pthread_join(prod_thread, NULL);
    pthread_join(cons_thread, NULL);

    // Destroy semaphores
    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex);

    return 0;
}
