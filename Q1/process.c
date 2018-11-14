#include "include/process.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

Process* process_initialize(int arrt,int burst) {
  //Values to set to when making a process
  Process* p = (Process*)malloc(sizeof(Process));
  p->pid = -1;
  p->state = 0;
  p->wait_time = 0 ;
  p->scheduling_policy = NULL;
  p->time_quantum = -1;
  p->preemption = -1;

  p->time = arrt;
  p->cpu_burst = burst;
  p->saved_burst = burst;
  return p;
}

void process_print(Process* p) {
  printf("Process Information");
  // printf("%d\n", p );
  printf(" pid: %d", p->pid);
  printf(" state %c", p->state);
  printf(" arrival_time %d", p->time);
  printf(" cpu_burst: %d", p->cpu_burst);
  printf(" saved_burst: %d", p->saved_burst);
  printf(" wait_time %d", p->wait_time);
  // printf("scheduling_policy %c", *(p->scheduling_policy));
  printf(" time_quantum: %d", p->time_quantum);
  printf(" preemption: %d\n",p->preemption);
}
