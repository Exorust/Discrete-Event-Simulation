#ifndef READY_QUEUE
#define READY_QUEUE

#include "event.h"

#define MAX_SIZE_EVENT_QUEUE 1024

typedef struct Ready_Queue_FCFS_t {
  int current_size; //Starts from 0, filled will be current_size-1
  Process* heap[MAX_SIZE_EVENT_QUEUE]; //Array of pointers to the event queue array
} Ready_Queue_FCFS;

//Function Declarations
Ready_Queue_FCFS* ready_queue_FCFS_initialize();
void ready_queue_FCFS_swap(Ready_Queue_FCFS* , int ,int );
void ready_queue_FCFS_minheapify(Ready_Queue_FCFS* , int );
void ready_queue_FCFS_build_minheap (Ready_Queue_FCFS* );
void ready_queue_FCFS_push(Ready_Queue_FCFS* , Process* );
Process* ready_queue_FCFS_pop(Ready_Queue_FCFS* );
Process* ready_queue_FCFS_top(Ready_Queue_FCFS* );
int ready_queue_FCFS_size(Ready_Queue_FCFS*);

#endif
