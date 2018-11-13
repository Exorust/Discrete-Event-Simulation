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
  p->wait_time = -1 ;
  p->scheduling_policy = NULL;
  p->time_quantum = -1;
  p->preemption = -1;

  p->arrival_time = arrt;
  p->cpu_burst = burst;
}

void process_print(Process* p) {
  printf("Process Information\n");
  printf("pid: %d", pid);
  printf("state %c", state);
  printf("arrival_time %d", arrival_time);
  printf("cpu_burst: %d", cpu_burst);
  printf("wait_time %d", wait_time);
  printf("scheduling_policy %c", *scheduling_policy);
  printf("time_quantum: %d", time_quantum);
  printf("preemption: %d", preemption);
}
