/*
Sinanis Andreas csd5150
*/

#ifndef HEADER_H
#define HEADER_H

#include <pthread.h>

extern pthread_mutex_t mutex, studying_mutex, printSt_m, creation_mutex;
extern pthread_cond_t cond, cond_btoa, all_students_created_cond;

extern int UniSize, BusSize;
extern int students_created;

typedef enum uni_type {MATH, PSY, CHEM, CSD} uni_type_t;

typedef struct student_t {
    int time_Studying;
    int AM;
    uni_type_t id_Uni;
    int state;
    pthread_t t;
} student_t;

typedef struct bus_T {
    int cap;
    int arr[4];
    pthread_t t;
} bus_t;

typedef struct node {
    student_t *s;
    struct node *next;
} node_t;

extern node_t *stopA_l, *stopB_l, *bus_l, *uni_l;
extern bus_t bus;

char *printUni(uni_type_t id);
void add_l(node_t **p, student_t *s);
node_t* delete_l(node_t **head, int AM);
void printFunc();
void student_create(student_t *s);
void* student(void *arg);
void busSeats();
void AtoB();
void BtoA();
void* busRoutine();
void freeList(node_t **list);

#endif
