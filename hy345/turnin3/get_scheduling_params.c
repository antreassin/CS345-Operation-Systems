#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/syscalls.h>
#include <asm-generic/errno-base.h>
#include <asm/uaccess.h>
#include <linux/d_params.h>

asmlinkage long sys_get_scheduling_params(struct d_params * params){
	struct task_struct *curr_s;
	printk("Get scheduling params,Sinanis Andreas, csd5150 \n");
	if(params == NULL){
		printk("param is null\n");
		return EINVAL;
	}
	if(access_ok(VERIFY_WRITE,params,sizeof(struct d_params))==0){
		printk("cant write\n");
		return EINVAL;
	}
	curr_s = get_current();
	params->deadline_1 = curr_s->deadline_1;
	params->deadline_2 = curr_s->deadline_2;
	params->computation_time = curr_s->computation_time;
	if(copy_to_user(params,curr_s,sizeof(struct d_params*))){
		printk("error in copy\n");
		return EINVAL;
	}
	return 0;
}
