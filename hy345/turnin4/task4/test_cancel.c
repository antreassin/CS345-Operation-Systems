#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/syscall.h>
#include <time.h>

int set_scheduling_params(int D1, int D2, int C) {
    	return syscall(342, D1, D2, C);
}

int get_score() {
    	return syscall(344);
}

void busy_loop(int duration) {
 	clock_t start = clock();
	while ((clock() - start) < duration * CLOCKS_PER_SEC);
}

int main() {
  	pid_t pid;
	int status;
 	if ((pid = fork()) == 0) {
        	set_scheduling_params(3, 5, 2);
  		long score = get_score();
	       	printf("score = %ld\n", score);
	       	busy_loop(6);
 	       	printf("finished\n");
        	return 0;
	}
	waitpid(pid, &status, 0);
    	if (WIFSIGNALED(status)) {
        	printf("P1 was killed as expected (Signal: %d).\n", WTERMSIG(status));
    	} else {
        	printf("P1 completed unexpectedly.\n");
    	}
	return 0;
}
