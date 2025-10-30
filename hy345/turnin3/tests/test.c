#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#define NR_dummy_sys 341

int main(void){
printf("Trap to kernel level\n");
syscall( NR_dummy_sys, 42); /* you should check return value for errors */
printf("Back to user level\n");
return 0;
}
