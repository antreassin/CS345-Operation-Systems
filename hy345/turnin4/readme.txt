Assign4 csd5150
 
Gia na dhmiourgisoume neo algorithmo xronoprogrammatismou, ton HVF, arxika tha prepei na ftiaksoume ena neo sched_class poy tha ulopoiei tis vasikes litourgies tou sched_class, to class auto tha einai endiamesa apo to rt kai cfs, dhladh, to .next pointer tou rf class tha dixnei sto &hvf_sched_class kai to .next pointer tou hvf_sched_class tha dixnei sto cfs.
Etsi exoume, 
 static const struct sched_class hvf_sched_class = {
        .next = &fair_sched_class,
        .enqueue_task = enqueue_task_fair,
        .dequeue_task = dequeue_task_fair,
        .pick_next_task = pick_next_task_fair,
        .check_preempt_curr = check_preempt_wakeup,
        .task_tick = task_tick_fair,
};
opws blepoume odws ulopoiei tis vasikes litourgies toy cfs.
 
Oi allages pou ekana sto pick_next_task, htan na prostesw ta eksis,
        struct task_struct *highest_task = NULL;
        long highest_value , value;
        highest_value = -1;
        for_each_process(p){
                if (!p ||p->state == TASK_DEAD||!p->deadline_1||!p->deadline_2||!p->computation_time)continue;
                value = get_score(p);
                if (value > highest_value) {
                        highest_value = value;
                        highest_task = p;
                }
        }
        if (highest_task) {
                printk("task pid=%d, value=%ld selected\n", highest_task->pid, highest_value);
                set_next_entity(cfs_rq, &highest_task->se);
                group_cfs_rq(&highest_task->se);
                hrtick_start_fair(rq, highest_task);
                return highest_task;
        }
opou epilegei meso tou for_each_process ekeino me to megalutero value

gia na skotosei process to opoio exei dhlswei x computation_time,  alla trexei gia x+c xrono, auto to kanw handle ws eksis
sthn task_tick_fair prostetw,
struct timespec ct = current_kernel_time();
        long et = ct.tv_sec - curr->deadline_1;
        if (curr->state == TASK_DEAD||!curr || curr->computation_time == 0) {
                return;
        }
        if (et >= curr->computation_time) {
                printk("killing task pid=%d no time\n",curr->pid);
                struct siginfo info;
                memset(&info, 0, sizeof(struct siginfo));
                info.si_signo = 9;
                info.si_code = SI_KERNEL;
                if (send_sig_info(9, &info, curr) < 0) {
                        printk("failed siganl for pid=%d\n", curr->pid);
                }
                return;
        }

to opoio koitaei an to current task exei parei parapanw wra apo osi xreiazetai.

gia kathe allh peripstwsh suneixei me to default xronopogrammatisti.  

ta duo test, test.c test_cancel.c to ena gia th dokimh 2 process me score 50,80 kai to allo gia thn dikimh tou an stamataei to process afou exei peruse to computation_time tou.