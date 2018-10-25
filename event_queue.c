#include "include/event_queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

Event* event_initialize(double inp_time) {
  Event* e = (Event*)malloc(sizeof(Event));
  e->time = inp_time;
  return e;
}

Event_Queue* event_queue_initialize() {
  Event_Queue* e = (Event_Queue*)malloc(sizeof(Event_Queue));
  int i;
  for(i=0;i<MAX_SIZE_EVENT_QUEUE;i++) {
    e->heap[i] = NULL;
  }
  e->current_size = 0;
  return e;
}

void event_queue_swap(Event_Queue* e, int i,int j) {
  //Swaps two processes in the event queue
  Event* temp = e->heap[i];
  e->heap[i] = e->heap[j];
  e->heap[j] = temp;
}

void event_queue_minheapify(Event_Queue* e, int i) {
  int left = 2*i+1;
  int right = 2*i+2;
  int n = e->current_size;
  int to_repeat = i;
  if(left<=n-1 && e->heap[i]->time > e->heap[right]->time) {
    to_repeat = right;
  }
  if(right<=n-1 && e->heap[i]->time > e->heap[left]->time) {
    to_repeat = left;
  }
  if(to_repeat != i) {
    event_queue_swap(e,i,to_repeat);
    event_queue_minheapify(e,to_repeat);
  }
}

void event_queue_build_minheap (Event_Queue* e) {
  int i;
  int n = e->current_size;
  for(i = n/2 ;i >= 1 ;i--){
    event_queue_minheapify(e,i) ;
  }
}

void event_queue_push(Event_Queue* e, Event* ev) {
  assert(e->current_size < MAX_SIZE_EVENT_QUEUE);
  e->heap[e->current_size] = ev;
  e->current_size++;
  event_queue_build_minheap(e);
}

Event* event_queue_pop(Event_Queue* e) {
  assert(e->current_size >0);
  int n = e-> current_size;
  event_queue_swap(e,0,(n-1));
  Event* ev = e->heap[n-1];
  e->heap[n-1] = NULL;
  event_queue_minheapify(e,0);
  return ev;
}

Event* event_queue_top(Event_Queue* e) {
  Event* ev = e->heap[0];
  return ev;
}

// //If needed implement DELETE
// void event_queue_delete(Event_Queue* e, Event* ev) {
//   assert(e->current_size >0);
//   e->heap[current_size] = ev;
//   event_queue_build_minheap(e);
// }
