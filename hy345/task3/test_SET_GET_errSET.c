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
	long d1 = -1, d2 = 200, c = 30;
	printf("Setting offset for deadline_1: %ld, deadline_2: %ld, and computation time: %ld\n(case, negative d1)",d1,d2,c);
	if(set_scheduling_params(d1,d2,c)!=0){
        printf("Error in set_scheduling_params\nfor params: deadline_1: %ld, deadline_2: %ld, and computation time: %ld\n",d1,d2,c);
    }

    d1 = 1; d2 = -1; c = 30;
    printf("Setting offset for deadline_1: %ld, deadline_2: %ld, and computation time: %ld\n(case, negative d2)",d1,d2,c);
    if(set_scheduling_params(d1,d2,c)!=0){
        printf("Error in set_scheduling_params\nfor params: deadline_1: %ld, deadline_2: %ld, and computation time: %ld\n",d1,d2,c);
    }

    d1 = 1; d2 = 200; c = -1;
    printf("Setting offset for deadline_1: %ld, deadline_2: %ld, and computation time: %ld\n(case, negative computation_time)",d1,d2,c);
    if(set_scheduling_params(d1,d2,c)!=0){
        printf("Error in set_scheduling_params\nfor params: deadline_1: %ld, deadline_2: %ld, and computation time: %ld\n",d1,d2,c);
    }

    d1 = 1; d2 = 2; c = 3000;
    printf("Setting offset for deadline_1: %ld, deadline_2: %ld, and computation time: %ld\n(case, computation>d2-d1)",d1,d2,c);
    if(set_scheduling_params(d1,d2,c)!=0){
        printf("Error in set_scheduling_params\nfor params: deadline_1: %ld, deadline_2: %ld, and computation time: %ld\n",d1,d2,c);
    }
    return 0;
}