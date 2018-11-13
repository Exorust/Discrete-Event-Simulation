#include "include/event_heap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>



Event_Heap* event_heap_initialize() {
  Event_Heap* e = (Event_Heap*)malloc(sizeof(Event_Heap));
  int i;
  for(i=0;i<MAX_SIZE_EVENT_HEAP;i++) {
    e->heap[i] = NULL;
  }
  e->current_size = 0;
  return e;
}

void event_heap_swap(Event_Heap* e, int i,int j) {
  //Swaps two processes in the event queue
  Event* temp = e->heap[i];
  e->heap[i] = e->heap[j];
  e->heap[j] = temp;
}

void event_heap_minheapify(Event_Heap* e, int i) {
  int left = 2*i+1;
  int right = 2*i+2;
  int n = e->current_size;
  int to_repeat = i;
  if(left<=n-1 && e->heap[i]->time > e->heap[left]->time) {
    to_repeat = right;
  }
  if(right<=n-1 && e->heap[i]->time > e->heap[right]->time) {
    to_repeat = left;
  }
  if(to_repeat != i) {
    event_heap_swap(e,i,to_repeat);
    event_heap_minheapify(e,to_repeat);
  }
}

void event_heap_build_minheap (Event_Heap* e) {
  int i;
  int n = e->current_size;
  for(i = n/2 ;i >= 1 ;i--){
    event_heap_minheapify(e,i) ;
  }
}

void event_heap_push(Event_Heap* e, Event* ev) {
  assert(e->current_size < MAX_SIZE_EVENT_HEAP);
  e->heap[e->current_size] = ev;
  e->current_size++;
  event_heap_build_minheap(e);
}

Event* event_heap_pop(Event_Heap* e) {
  assert(e->current_size >0);
  int n = e-> current_size;
  event_heap_swap(e,0,(n-1));
  Event* ev = e->heap[n-1];
  e->heap[n-1] = NULL;
  event_heap_minheapify(e,0);
  return ev;
}

Event* event_heap_top(Event_Heap* e) {
  Event* ev = e->heap[0];
  return ev;
}

int event_heap_size(Event_Heap* e) {
  return e->current_size;
}

// //If needed implement DELETE
// void event_heap_delete(Event_Heap* e, Event* ev) {
//   assert(e->current_size >0);
//   e->heap[current_size] = ev;
//   event_heap_build_minheap(e);
// }
