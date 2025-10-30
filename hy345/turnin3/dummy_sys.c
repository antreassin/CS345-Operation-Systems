#include <linux/kernel.h>

asmlinkage long sys_dummy_sys(int arg0){
	printk("called dummy_sys, %d \n",arg0);
	return ((long)arg0*3);
}
