#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_THREADS 5

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int shared_counter = 0;

void* thread_function(void* arg) {
    int thread_id = *(int*)arg;
    
    for (int i = 0; i < 3; i++) {
        pthread_mutex_lock(&mutex);
        
        shared_counter++;
        printf("Thread %d: Counter = %d\n", thread_id, shared_counter);
        
        pthread_mutex_unlock(&mutex);
        
        usleep(100000); // Sleep for 100ms
    }
    
    free(arg);
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    
    printf("Starting multithreading example\n");
    printf("Creating %d threads...\n\n", NUM_THREADS);
    
    // Create threads
    for (int i = 0; i < NUM_THREADS; i++) {
        int* thread_id = malloc(sizeof(int));
        *thread_id = i + 1;
        
        if (pthread_create(&threads[i], NULL, thread_function, thread_id) != 0) {
            perror("pthread_create failed");
            exit(1);
        }
    }
    
    // Wait for all threads to complete
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    
    printf("\nAll threads completed\n");
    printf("Final counter value: %d\n", shared_counter);
    printf("Expected value: %d\n", NUM_THREADS * 3);
    
    pthread_mutex_destroy(&mutex);
    
    return 0;
}
