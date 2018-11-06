#include "include/ready_queue_FCFS.h"
#include "include/event.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>



Ready_Queue_FCFS* ready_queue_FCFS_initialize() {
  Ready_Queue_FCFS* e = (Ready_Queue_FCFS*)malloc(sizeof(Ready_Queue_FCFS));
  int i;
  for(i=0;i<MAX_SIZE_EVENT_QUEUE;i++) {
    e->heap[i] = NULL;
  }
  e->current_size = 0;
  return e;
}

void ready_queue_FCFS_swap(Ready_Queue_FCFS* e, int i,int j) {
  //Swaps two processes in the event queue
  Event* temp = e->heap[i];
  e->heap[i] = e->heap[j];
  e->heap[j] = temp;
}

void ready_queue_FCFS_minheapify(Ready_Queue_FCFS* e, int i) {
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
    ready_queue_FCFS_swap(e,i,to_repeat);
    ready_queue_FCFS_minheapify(e,to_repeat);
  }
}

void ready_queue_FCFS_build_minheap (Ready_Queue_FCFS* e) {
  int i;
  int n = e->current_size;
  for(i = n/2 ;i >= 1 ;i--){
    ready_queue_FCFS_minheapify(e,i) ;
  }
}

void ready_queue_FCFS_push(Ready_Queue_FCFS* e, Event* ev) {
  assert(e->current_size < MAX_SIZE_EVENT_QUEUE);
  e->heap[e->current_size] = ev;
  e->current_size++;
  ready_queue_FCFS_build_minheap(e);
}

Event* ready_queue_FCFS_pop(Ready_Queue_FCFS* e) {
  assert(e->current_size >0);
  int n = e-> current_size;
  ready_queue_FCFS_swap(e,0,(n-1));
  Event* ev = e->heap[n-1];
  e->heap[n-1] = NULL;
  ready_queue_FCFS_minheapify(e,0);
  return ev;
}

Event* ready_queue_FCFS_top(Ready_Queue_FCFS* e) {
  Event* ev = e->heap[0];
  return ev;
}

// //If needed implement DELETE
// void ready_queue_FCFS_delete(Ready_Queue_FCFS* e, Event* ev) {
//   assert(e->current_size >0);
//   e->heap[current_size] = ev;
//   ready_queue_FCFS_build_minheap(e);
// }
