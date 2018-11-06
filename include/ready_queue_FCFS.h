#include "event.h"

#ifndef READY_QUEUE
#define READY_QUEUE

#define MAX_SIZE_EVENT_QUEUE 1024

typedef struct Ready_Queue_FCFS_t {
  int current_size; //Starts from 0, filled will be current_size-1
  Event* heap[MAX_SIZE_EVENT_QUEUE]; //Array of pointers to the event queue array
} Ready_Queue_FCFS;

//Function Declarations
Event* event_initialize(double);
Ready_Queue_FCFS* ready_queue_FCFS_initialize();
void ready_queue_FCFS_swap(Ready_Queue_FCFS*, int,int);
void ready_queue_FCFS_minheapify(Ready_Queue_FCFS*, int);
void ready_queue_FCFS_build_minheap (Ready_Queue_FCFS*);

#endif
