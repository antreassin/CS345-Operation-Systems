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
	long d1 = 1, d2 = 200, c = 30;
	printf("Setting params d1: %ld, d2: %ld, c: %ld\n",d1,d2,c);
	if(set_scheduling_params(d1, d2, c)!=0){
		printf("error in set\n");
	}

	if(get_scheduling_params(&params)!=0){
		printf("error in get\n");
	}


	printf("getting params d1: %ld, d2: %ld, c: %ld\n",params.deadline_1,params.deadline_2,params.computation_time);
	sleep(2);	
	printf("score: %ld\n",get_scheduling_score());
	return 0;
}
