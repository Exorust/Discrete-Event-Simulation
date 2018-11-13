#ifndef EVENT_HEAP
#define EVENT_HEAP

#include "event.h"

#define MAX_SIZE_EVENT_HEAP 1024

typedef struct Event_Heap_t {
  int current_size; //Starts from 0, filled will be current_size-1
  Process* heap[MAX_SIZE_EVENT_QUEUE]; //Array of pointers to the event queue array
} Event_Heap;

//Function Declarations
Event_Heap* ready_queue_initialize();
void ready_queue_swap(Event_Heap* , int ,int );
void ready_queue_minheapify(Event_Heap* , int );
void ready_queue_build_minheap (Event_Heap* );
void ready_queue_push(Event_Heap* , Event* );
Event* ready_queue_pop(Event_Heap* );
Event* ready_queue_top(Event_Heap* );
int ready_queue_size(Event_Heap*);

#endif
