#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/syscalls.h>
#include <asm-generic/errno-base.h>
#include <asm/uaccess.h>
#include <linux/d_params.h>

asmlinkage long sys_get_scheduling_score(){
	struct task_struct *curr_s;
	struct timespec curr_t;	
	printk("Get scheduling score ,Sinanis Andreas, csd5150 \n");
	long D1, D2, D3;
	curr_s = get_current();
	curr_t = current_kernel_time();
	D1 = curr_s->deadline_1;
	D2 = curr_s->deadline_2;
	curr_t = current_kernel_time();
	D3 = curr_t.tv_sec;
	if(D3 < D1){
		return 100;
	}else if(D3 > D2){
		return 0;
	}else{
		return ((D2 - D3) * 100)/(D2 - D1);
	}
}
