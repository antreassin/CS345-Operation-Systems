#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/syscall.h>
#include <time.h>

int set_scheduling_params(int D1, int D2, int C) {
    return syscall(342,D1, D2, C);
}

int get_score(){
    return syscall(344);
}

void busy_loop(int duration) {
    clock_t start = clock();
    while((clock()-start)<duration*CLOCKS_PER_SEC);
}

int main() {
    	pid_t pid1, pid2;
    	if ((pid1 = fork()) == 0){
		set_scheduling_params(3, 7, 5);
     		long score = get_score();
       		printf("score = %ld \n",score);
        	busy_loop(5);
        	printf("P1 finished\n");
        	return 0;
    	}
   	sleep(1);
	/*Gia na eimai sigouros oti to p2 tha ginei meta to p1*/
    	if ((pid2 = fork()) == 0) {
       		set_scheduling_params(4, 9, 5);
       		long score = get_score();
       		printf("score = %ld \n",score);
        	busy_loop(5);
        	printf("Process 2 finished.\n");
        	return 0;
    }
    wait(NULL);
    wait(NULL);
    return 0;
}
