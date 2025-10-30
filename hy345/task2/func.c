/*
Sinanis Andreas csd5150
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include "header.h"

pthread_mutex_t mutex, studying_mutex, printSt_m, creation_mutex;
pthread_cond_t cond, cond_btoa, all_students_created_cond;

int UniSize, BusSize;
int students_created = 0;

node_t *stopA_l = NULL, *stopB_l = NULL, *bus_l = NULL, *uni_l = NULL;
bus_t bus;

char *printUni(uni_type_t id) {
    switch (id) {
        case MATH: 
            return"MATH";
        case PSY: 
            return "PSY";
        case CHEM: 
            return "CHEM";
        case CSD: 
            return "CSD";
        default: 
            return "";
    }
    return "";
}

void add_l(node_t **p, student_t *s){
    pthread_mutex_lock(&creation_mutex);
        node_t *q = malloc(sizeof(node_t));
        if(q == NULL){
            perror("Error in list allocation\n");
            pthread_mutex_unlock(&creation_mutex);
            return;
        }
        q->s = s;
        q->next = NULL;

        if(*p == NULL){
            *p = q;
        } else {
            node_t *tmp = *p;
            while (tmp->next != NULL) {
                tmp = tmp->next;
            }
            tmp->next = q;
        }
    pthread_mutex_unlock(&creation_mutex);
}


node_t* delete_l(node_t **head, int AM) {
    if(*head == NULL){
        return NULL;
    }
    node_t *current = *head;
    node_t *previous = NULL;
    while(current != NULL && current->s->AM != AM){
        previous = current;
        current = current->next;
    }
    if(current == NULL){
        printf("Student %d not found in list\n", AM);
        return NULL;
    }
    if(previous == NULL){
        *head = current->next;
    }else{
        previous->next = current->next;
    }
    current->next = NULL;
    return current;
}

void printFunc(){
    pthread_mutex_lock(&printSt_m);
        node_t *tmp;
        printf("Stop A: ");
        tmp = stopA_l;
        while (tmp != NULL){
            printf("[%d, %s] ", tmp->s->AM, printUni(tmp->s->id_Uni));
            tmp = tmp->next;
        }
        printf("\nBus: ");
        tmp = bus_l;
        while (tmp != NULL){
            printf("[%d, %s] ", tmp->s->AM, printUni(tmp->s->id_Uni));
            tmp = tmp->next;
        }
        printf("\nUniversity: ");
        tmp = uni_l;
        while (tmp != NULL){
            printf("[%d, %s] ", tmp->s->AM, printUni(tmp->s->id_Uni));
            tmp = tmp->next;
        }
        printf("\nStop B: ");
        tmp = stopB_l;
        while(tmp != NULL){
            printf("[%d, %s] ", tmp->s->AM, printUni(tmp->s->id_Uni));
            tmp = tmp->next;
        }
        printf("\n\n");
    pthread_mutex_unlock(&printSt_m);
}

void student_create(student_t *s){
    s->id_Uni = rand() % 4;
    s->time_Studying = rand() % 11 + 5;
    add_l(&stopA_l, s);
}

void* student(void *arg){
    student_t *stdn = arg;

    pthread_mutex_lock(&mutex);
        student_create(stdn);
        printf("Student %d %s Created\n", stdn->AM,printUni(stdn->id_Uni));
        printFunc();
    pthread_mutex_unlock(&mutex);

    pthread_mutex_lock(&creation_mutex);
        students_created++;
        if(students_created == UniSize){
            pthread_cond_signal(&all_students_created_cond);
        }
    pthread_mutex_unlock(&creation_mutex);

    pthread_mutex_lock(&studying_mutex);
        while (stdn->state == 0){
            pthread_cond_wait(&cond, &studying_mutex);
        }
    pthread_mutex_unlock(&studying_mutex);

    sleep(stdn->time_Studying);
    pthread_mutex_lock(&printSt_m);
        printf("Student %d: Done studying for %d seconds\n", stdn->AM, stdn->time_Studying);
        node_t *droppedS = delete_l(&uni_l, stdn->AM);
        if(droppedS != NULL){
            add_l(&stopB_l, droppedS->s);
            free(droppedS);
        }
        pthread_cond_signal(&cond_btoa);
    pthread_mutex_unlock(&printSt_m);
    printFunc();

    return NULL;
}

void busSeats(){
    for(int i = 0; i < 4; i++) {
        bus.arr[i] = BusSize / 4;
    }
}

void AtoB(){
    node_t *curr = stopA_l;

    while (curr != NULL){
        if (bus.arr[curr->s->id_Uni] > 0){
            printf("Student %d (%s) boarded the bus\n", curr->s->AM, printUni(curr->s->id_Uni));
            bus.arr[curr->s->id_Uni]--;
            node_t *boardedS = delete_l(&stopA_l, curr->s->AM);
            if (boardedS != NULL) {
                add_l(&bus_l, boardedS->s);
                free(boardedS);
            }
            curr = stopA_l;
            printFunc();
        } else{
            curr = curr->next;
        }
    }
    curr = stopA_l;
    while (curr != NULL){
        printf("Student %d (%s) could not board the bus\n\n", curr->s->AM, printUni(curr->s->id_Uni));
        curr = curr->next;
    }

    printf("Bus is on the way to University\n");
    sleep(10);
    printf("Bus arrived at University\n\n");

    pthread_mutex_lock(&studying_mutex);
        curr = bus_l;
        while(curr != NULL){
            printf("Student %d (%s) went to University\n", curr->s->AM, printUni(curr->s->id_Uni));
            curr->s->state = 1;

            node_t *droppedS = delete_l(&bus_l, curr->s->AM);
            if (droppedS != NULL) {
                add_l(&uni_l, droppedS->s);
                free(droppedS);
            }
            printFunc();
            curr = bus_l;
        }
        pthread_cond_broadcast(&cond);
    pthread_mutex_unlock(&studying_mutex);

    sleep(3);
    busSeats();
}

void BtoA() {
    node_t *curr = stopB_l;
    while(curr != NULL){
        if(bus.arr[curr->s->id_Uni] > 0){
            printf("Student %d (%s) boarded the bus\n", curr->s->AM, printUni(curr->s->id_Uni));
            bus.arr[curr->s->id_Uni]--;
            node_t *boardedS = delete_l(&stopB_l, curr->s->AM);
            if (boardedS != NULL){
                add_l(&bus_l, boardedS->s);
                free(boardedS);
            }
            curr = stopB_l;
            printFunc();
        }else{
            curr = curr->next;
        }
    }

    printf("Bus is heading to stop A\n\n");
    sleep(10);
    printf("Bus arrived to Stop A\n\n");

    curr = bus_l;
    while(curr != NULL){
        printf("Student %d (%s) went home\n\n", curr->s->AM, printUni(curr->s->id_Uni));
        delete_l(&bus_l, curr->s->AM);
        curr = bus_l;
    }

    sleep(3);

    busSeats();
}

void* busRoutine(){
    pthread_mutex_lock(&creation_mutex);
        while(students_created < UniSize){
            pthread_cond_wait(&all_students_created_cond, &creation_mutex);
        }
    pthread_mutex_unlock(&creation_mutex);

    while(stopA_l != NULL || stopB_l != NULL || uni_l != NULL){
        pthread_mutex_lock(&mutex);
        AtoB();
        BtoA();
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

void freeList(node_t **list){
    while(*list != NULL){
        node_t *temp = *list;
        *list = (*list)->next;
        free(temp->s);
        free(temp);
    }
}
