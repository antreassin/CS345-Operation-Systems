#include <stdio.h>
#include <unistd.h>

#define set_scheduling_params(arg0,arg1,arg2) syscall(342, arg0, arg1, arg2)
#define get_scheduling_params(a) syscall(343, a)
#define get_scheduling_score() syscall(344)

struct d_params{
	long deadline_1;
	long deadline_2;
	long computation_time;
};

int main(void){
	struct d_params params;
	long d1 = 1, d2 = 20, c = 30;
	printf("Setting offset for deadline_1: %ld, deadline_2: %ld, and computation time: %ld\n",d1,d2,c);
	if(set_scheduling_params(d1, d2, c)!=0){
		printf("error in set\n");
        return 1;
	}
    if(get_scheduling_params(&params)!=0){
		printf("error in get\n");
        return 1;
	}
    printf("(time)Deadline_1: %ld, (time)Deadline_2: %ld, and computation time %ld milliseconds\n",params.deadline_1%1000,params.deadline_2%1000,params.computation_time);	
	printf("\t case, score = 100\n");
	printf("score: %ld\n",get_scheduling_score());
	return 0;
}
