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

    SI_KERNEL
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


/
 * static long get_score(struct task_struct *p) {
        if(p->deadline_1>=p->deadline_2){
                return 0;
        }
        if (p->computation_time < p->deadline_1)
                return 100;
        else if (p->computation_time > p->deadline_2)
                return 0;
        else
                return ((p->deadline_2 - p->computation_time) * 100) / (p->deadline_2 - p->deadline_1);
}

static struct task_struct *pick_next_task_fair(struct rq *rq)
{
        struct task_struct *p;
        struct cfs_rq *cfs_rq = &rq->cfs;
        struct sched_entity *se;
        struct task_struct *highest_task = NULL;
        long highest_value , value;
        highest_value = -1;
        for_each_process(p){
                if (!p ||p->state == TASK_DEAD||!p->deadline_1||!p->deadline_2||!p->computation_time)continue;
                value = get_score(p);
                if (value > highest_value) {
                        highest_value = value;
                        highest_task = p;
                }
        }
        if (highest_task) {
                printk("Selected task pid=%d, value=%ld\n", highest_task->pid, highest_value);
                set_next_entity(cfs_rq, &highest_task->se);
                group_cfs_rq(&highest_task->se);
                hrtick_start_fair(rq, highest_task);
                return highest_task;
        }
**/