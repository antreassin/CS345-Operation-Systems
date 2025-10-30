/*
Sinanis Andreas csd5150
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include "header.h"

int main(int argc, char *argv[]){
    if (argc != 2){
        perror("Incompatible args\n");
        return 1;
    }

    BusSize = atoi(argv[1]);
    printf("Enter the number of students\n");
    scanf("%d", &UniSize);
    if(!(UniSize > 0 && UniSize < 200)){
        perror("University capacity should be between 1 and 200\n");
        return 1;
    }

    srand(time(NULL));

    pthread_mutex_init(&mutex, NULL);
    pthread_mutex_init(&printSt_m, NULL);
    pthread_mutex_init(&studying_mutex, NULL);
    pthread_mutex_init(&creation_mutex, NULL);
    pthread_cond_init(&cond, NULL);
    pthread_cond_init(&cond_btoa, NULL);
    pthread_cond_init(&all_students_created_cond, NULL);

    bus.cap = BusSize;
    busSeats();

    if (pthread_create(&bus.t, NULL, &busRoutine, NULL) != 0){
        perror("Failed to create bus thread\n");
        return 1;
    }

    pthread_t student_threads[UniSize];
    for(int i = 0; i < UniSize; i++){
        student_t *arg = malloc(sizeof(student_t));
        if (arg == NULL) {
            perror("Failed to allocate memory for student");
            exit(1);
        }
        arg->AM = i + 1;
        arg->state = 0;
        if (pthread_create(&arg->t, NULL, &student, arg) != 0) {
            perror("Failed to create student thread\n");
            free(arg);
            continue;
        }
        student_threads[i] = arg->t;
    }

    for(int i = 0; i < UniSize; i++){
        if (pthread_join(student_threads[i], NULL) != 0) {
            perror("Error in joining student thread\n");
        }
    }

    if(pthread_join(bus.t, NULL) != 0){
        perror("Failed to join bus thread\n");
    }

    freeList(&stopA_l);
    freeList(&stopB_l);
    freeList(&bus_l);
    freeList(&uni_l);

    pthread_mutex_destroy(&mutex);
    pthread_mutex_destroy(&studying_mutex);
    pthread_mutex_destroy(&printSt_m);
    pthread_mutex_destroy(&creation_mutex);
    pthread_cond_destroy(&cond);
    pthread_cond_destroy(&cond_btoa);
    pthread_cond_destroy(&all_students_created_cond);

    return 0;
}
