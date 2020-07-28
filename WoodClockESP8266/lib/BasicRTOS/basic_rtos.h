#ifndef _BASIC_RTOS_H
#define _BASIC_RTOS_H
#include <Arduino.h>

#define MAX_TASKS 256

/*
*  @brief: 
*  @notes: 
*/ 
typedef struct task_ctrl_blk_s{
    unsigned int sem;           // Semaphore flag 
    unsigned int *stack_top;    // Top of stack 
    unsigned int *stack_ptr;    // Current stack pointer
    void *(*task_ptr)(void*);   // Task function pointer
};

/*
*  @brief: 
*  @notes: 
*  @param: 
*  @returns: 
*/ 
void os_begin(void);

/*
*  @brief: 
*  @notes: 
*  @param: 
*  @returns: 
*/ 
void context_switch(void);

/*
*  @brief: 
*  @notes: 
*  @param: 
*  @returns: 
*/ 
inline void update_registers(void);

/*
*  @brief: 
*  @notes: 
*  @param: 
*  @returns: 
*/ 
inline void os_context_save(void);

/*
*  @brief: 
*  @notes: 
*  @param: 
*  @returns: 
*/  
inline void os_context_store(void);

/*
*  @brief: 
*  @notes: 
*  @param: 
*  @returns: 
*/  
inline void thdSleepSys(unsigned int sys_tick);
#endif 
