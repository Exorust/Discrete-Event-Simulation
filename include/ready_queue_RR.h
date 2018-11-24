#ifndef ROUND_ROBIN
#define ROUND_ROBIN

#include "process.h"


#define MAX_SIZE_ROUND_ROBIN 1024

typedef struct Ready_Queue_RR_t {
  int current_size; //Starts from 0, filled will be current_size-1 //Current location for pop
  Process* queue[MAX_SIZE_ROUND_ROBIN]; //Array of pointers to the event queue array
} Ready_Queue_RR;

//Function Declarations
Ready_Queue_RR* ready_queue_RR_initialize();
int ready_queue_RR_size(Ready_Queue_RR*);
void ready_queue_RR_push(Ready_Queue_RR*,Process*);
Process* ready_queue_RR_pop(Ready_Queue_RR*);
Process* ready_queue_RR_top(Ready_Queue_RR*);

#endif
