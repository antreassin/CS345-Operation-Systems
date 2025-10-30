#include <linux/sched.h>
#include <linux/kernel.h>
#include <asm-generic/errno-base.h>
#include <linux/syscalls.h>
#include <asm/uaccess.h>
#include <linux/errno.h>


asmlinkage long sys_set_scheduling_params(long deadline_1, long deadline_2, long computation_time ){
	struct timespec curr_t;
	/* Gia thn trith sunartish to D3 apo oti mporw na katalavw
	   einai o xronos thn stigmh pou kalestike to get_score,
	   o monos tropos gia na mhn einia ena poly megalos arithmos to 
	   D3 einai na prostesw sto set_params epishs ton xrono sta D1/2
	*/
	struct task_struct *curr_s;
	long time_param;
	printk("Set scheduling_param, Sinanis Andreas, csd5150\n");
	if(deadline_1 <= 0 || deadline_2 <= 0 || computation_time <= 0){
		printk("Args are less than 0\n");
		return EINVAL;
	}
	if((computation_time/1000) > (deadline_2-deadline_1)){
		printk("computation time cannot exceed\n");
		return EINVAL;
	}
	curr_t = current_kernel_time();
	time_param =  curr_t.tv_sec;
	curr_s = get_current();
	curr_s->deadline_1 = time_param + deadline_1;
	curr_s->deadline_2 = time_param + deadline_2;
	curr_s->computation_time = computation_time;
	return 0;
}
