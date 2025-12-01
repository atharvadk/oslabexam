//Implementation of Classical Reader Writer problem using Threads and Mutex.

// readers_writers.c
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdint.h>

// Shared data (critical resource)
int shared_data = 0;

// Count of active readers
int readcount = 0;

// Mutexes
pthread_mutex_t readcount_mutex;   // protects readcount
pthread_mutex_t resource_mutex;    // gives exclusive access to writers OR first/last reader

void *reader(void *arg) {
    int id = (int)(intptr_t)arg;

    while (1) {
        // Entry section for reader
        pthread_mutex_lock(&readcount_mutex);
        readcount++;
        if (readcount == 1) {
            // First reader locks the resource
            pthread_mutex_lock(&resource_mutex);
        }
        pthread_mutex_unlock(&readcount_mutex);

        // Critical section (reading)
        printf("Reader %d: reading shared_data = %d\n", id, shared_data);
        usleep(100000); // simulate read time (0.1 sec)

        // Exit section for reader
        pthread_mutex_lock(&readcount_mutex);
        readcount--;
        if (readcount == 0) {
            // Last reader unlocks the resource
            pthread_mutex_unlock(&resource_mutex);
        }
        pthread_mutex_unlock(&readcount_mutex);

        // Remainder section
        usleep(200000); // simulate some delay before next read
    }

    return NULL;
}

void *writer(void *arg) {
    int id = (int)(intptr_t)arg;

    while (1) {
        // Entry section for writer
        pthread_mutex_lock(&resource_mutex); // exclusive access

        // Critical section (writing)
        shared_data++;
        printf("Writer %d: updated shared_data to %d\n", id, shared_data);
        usleep(150000); // simulate write time (0.15 sec)

        // Exit section for writer
        pthread_mutex_unlock(&resource_mutex);

        // Remainder section
        usleep(300000); // simulate some delay before next write
    }

    return NULL;
}

int main() {
    int i;
    const int NUM_READERS = 5;
    const int NUM_WRITERS = 2;

    pthread_t readers[NUM_READERS];
    pthread_t writers[NUM_WRITERS];

    // Initialize mutexes
    pthread_mutex_init(&readcount_mutex, NULL);
    pthread_mutex_init(&resource_mutex, NULL);

    // Create reader threads
    for (i = 0; i < NUM_READERS; i++) {
        if (pthread_create(&readers[i], NULL, reader, (void *)(intptr_t)(i + 1)) != 0) {
            perror("Failed to create reader thread");
            exit(EXIT_FAILURE);
        }
    }

    // Create writer threads
    for (i = 0; i < NUM_WRITERS; i++) {
        if (pthread_create(&writers[i], NULL, writer, (void *)(intptr_t)(i + 1)) != 0) {
            perror("Failed to create writer thread");
            exit(EXIT_FAILURE);
        }
    }

    // Join threads (in practice this never returns because loops are infinite)
    for (i = 0; i < NUM_READERS; i++) {
        pthread_join(readers[i], NULL);
    }
    for (i = 0; i < NUM_WRITERS; i++) {
        pthread_join(writers[i], NULL);
    }

    // Destroy mutexes (unreachable here, but good practice)
    pthread_mutex_destroy(&readcount_mutex);
    pthread_mutex_destroy(&resource_mutex);

    return 0;
}

/*
Sample Output (program runs with no stdin; prints reader/writer actions):

This program creates 5 readers and 2 writers. Output is interleaved and time-dependent.
Example excerpt:
Writer 1: updated shared_data to 1
Reader 1: reading shared_data = 1
Reader 2: reading shared_data = 1
Reader 3: reading shared_data = 1
Writer 2: updated shared_data to 2
Reader 4: reading shared_data = 2
Reader 5: reading shared_data = 2
Writer 1: updated shared_data to 3
Reader 1: reading shared_data = 3
...

Notes:
- Exact ordering will vary due to thread scheduling and sleep durations.
- Readers may read the same value concurrently; writers get exclusive access and increment `shared_data`.
- To compile on Windows with POSIX threads (MSYS2/MinGW):

    gcc -o reader_writer Reader_Writer.c -lpthread -lrt

Then run:
    ./reader_writer

To modify the number of readers/writers or timings, change `NUM_READERS`, `NUM_WRITERS`,
and the `usleep(...)` values inside the reader/writer functions.
*/
