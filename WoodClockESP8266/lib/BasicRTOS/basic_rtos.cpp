#include <basic_rtos.h>

unsigned int os_curr_tid;                   // OS current task ID. 
unsigned int os_sem;                        // OS semaphore flag
unsigned int num_tasks;                     // Current Number of active tasks
task_ctrl_blk_s os_task_switch[MAX_TASKS];  // Task array stack

