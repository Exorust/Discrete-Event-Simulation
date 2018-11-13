#include "include/ready_queue_RR.h"
#include "include/process.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


Ready_Queue_RR* ready_queue_RR_initialize() {
  Ready_Queue_RR* q = (Ready_Queue_RR*)malloc(sizeof(Ready_Queue_RR));
  int i;
  for(i=0;i<MAX_SIZE_ROUND_ROBIN;i++) {
    q->queue[i] = NULL;
  }
  q->current_size = 0;
  return q;
}

int ready_queue_RR_size(Ready_Queue_RR* q) {
  return q->current_size;
}

void ready_queue_RR_push(Ready_Queue_RR* q, Process* e){
  int index = ready_queue_RR_size(q);
  assert(q->queue[index] == NULL);
  q->queue[q->current_size] = e;
  q->current_size++;   //Breakkdown?
}

Process* ready_queue_RR_pop(Ready_Queue_RR* q) {
  Process* e = q->queue[0];
  int i;
  for(i=0;i<q->current_size;i++){
    q->queue[i] = q->queue[i+1];
  }
  q->current_size--; //Breakkdown??
  return e;
}

Process* ready_queue_RR_top(Ready_Queue_RR* q) {
  Process* e = q->queue[0];
  return e;
}
