#ifndef EVENT_HEAP
#define EVENT_HEAP

#include "event.h"

#define MAX_SIZE_EVENT_HEAP 1024

typedef struct Event_Heap_t {
  int current_size; //Starts from 0, filled will be current_size-1
  Event* heap[MAX_SIZE_EVENT_HEAP]; //Array of pointers to the event queue array
} Event_Heap;

//Function Declarations
Event_Heap* event_heap_initialize();
void event_heap_swap(Event_Heap* , int ,int );
void event_heap_minheapify(Event_Heap* , int );
void event_heap_build_minheap (Event_Heap* );
void event_heap_push(Event_Heap* , Event* );
Event* event_heap_pop(Event_Heap* );
Event* event_heap_top(Event_Heap* );
int event_heap_size(Event_Heap*);

#endif
