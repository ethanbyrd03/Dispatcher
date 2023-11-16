// PID: 730481481
// I pledge the COMP211 honor code.
// -----------------------------------
//  COMP 211 - Systems Fundamentals
//
//  Fall 2022 - Lab 6
// -----------------------------------

#include "task.h"
#include "sim.h"
#include <stdio.h>
#include <stdlib.h>

// ------------------------------------
// Function prototype
// ------------------------------------
//  Description:
//    Runs the linked list of task_structs using a scheduling queue. 
//    This should be done by:
//      - Scheduling the tasks (min heapifying the linked list)
//      - Until the queue is empty:
//          - remove and run the highest priority task in the queue
//          - appending the task back on to the queue if it was not completed
//          - re-scheduling the tasks
//
//  Arguments:
//    cycles_per_task: positive integer number of CPU cycles
//
//  Return:
//    None
           
void dispatcher(unsigned int cycles_per_task) {
    struct task_struct* head = NULL;
    schedule();
    while (head != NULL) {
        struct task_struct* highestPriorityTask = head;
        if (highestPriorityTask != NULL) {
            highestPriorityTask->remaining_cycles -= cycles_per_task;
            if (highestPriorityTask->remaining_cycles <= 0) {
                struct task_struct* result = remove_task(highestPriorityTask->pid);
                if (result != NULL) {
                    printf("Task with PID %u completed\n", highestPriorityTask->pid);
                    free(highestPriorityTask);
                } else {
                    printf("Error removing completed task (PID: %u)\n", highestPriorityTask->pid);
                }
            } else {
                unsigned int result = append_task(highestPriorityTask->pid, highestPriorityTask->priority, highestPriorityTask->remaining_cycles);
                if (result == 0) {
                    printf("Task with PID %u appended back to the queue\n", highestPriorityTask->pid);
                } else {
                    printf("Error appending task back to the queue (PID: %u)\n", highestPriorityTask->pid);
                }
            }
        }
        schedule();
    }
} // end dispatcher() function

// ------------------------------------
// Function prototype
// ------------------------------------
//  Description:
//    Simulate running a task by:
//      - decrementing the number of remaining cycles for the task
//      - printing out "Task {pid} run for {num_cycles} cycle(s)."
//      - if the task is completed, also printing out "Task {pid} Completed."
//
//  Arguments:
//    task: a pointer to the task_struct to be run
//    num_cycles: the number of CPU cycles to simulate
//
//  Return:
//    None

void run(task_struct* task, unsigned int num_cycles) {
    if (task == NULL) {
        printf("Invalid task pointer\n");
        return;
    }
    if (task->remaining_cycles <= 0) {
        printf("Task with PID %u is already completed\n", task->pid);
        return;
    }
    if (num_cycles >= (unsigned) task->remaining_cycles) {
        printf("Task with PID %u run for %u cycle(s).\n", task->pid, task->remaining_cycles);
        printf("Task with PID %u completed.\n", task->pid);
        task->remaining_cycles = 0;
    } else {
        printf("Task with PID %u run for %u cycle(s).\n", task->pid, num_cycles);
        task->remaining_cycles -= num_cycles;
    } 
} // end run() function
