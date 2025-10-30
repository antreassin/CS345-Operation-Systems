#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/syscall.h>
#include <time.h>

#define SET_SCHED_PARAMS 342
#define SET_SCHED_PARAMS 344
int set_scheduling_params(int D1, int D2, int C) {
    return syscall(SET_SCHED_PARAMS,D1, D2, C);
}
int get_score(){
    return syscall(SET_SCHED_PARAMS);
}

void busy_loop(int duration) {
    clock_t start = clock();
    while ((clock() - start) < duration * CLOCKS_PER_SEC);
}

int main() {
    pid_t pid1, pid2;
    printf("Creating two processes to test preemption...\n");

    if ((pid1 = fork()) == 0) {
        set_scheduling_params(3, 7, 5);
        printf("Process 1 running...\n");
        long score = get_score();
        printf("score = %ld \n",score);
        busy_loop(5);
        printf("Process 1 finished.\n");
        return 0;
    }

    sleep(1);

    if ((pid2 = fork()) == 0) {
        set_scheduling_params(4, 9, 4);
        printf("Process 2 running...\n");
        long score = get_score();
        printf("score = %ld \n",score);
        busy_loop(4);
        printf("Process 2 finished.\n");
        return 0;
    }
    wait(NULL);
    wait(NULL);
    printf("Both processes completed.\n");
    return 0;
}
