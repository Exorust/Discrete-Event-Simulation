#include "include/process_table.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

Process_Table* process_table_initialize() {
  //Values to set to when making a process
  Process_Table* p = (Process_Table*)malloc(sizeof(Process_Table));
   int i;
  for(i=0;i<MAX_SIZE_PROCESS_TABLE;i++) {
    p->proc_arr[i] = NULL;
  }
  p->current_size = 0;
}

int process_table_full(Process_Table* pt) {
  //Returns -1 if full else returns a the index which is free
  if(pt->current_size == MAX_SIZE_PROCESS_TABLE){
    return -1;
  }
  int i;
  for(i=0;i<MAX_SIZE_PROCESS_TABLE;i++) {
    if(pt->proc_arr[i] == NULL) {
      return i;
    }
  }
  abort();
}

void process_table_add(Process_Table* pt,Process* p) {
  int index = process_table_full(pt);
  assert(index != -1);
  pt->proc_arr[index] = p;
  p->pid = index;
  pt->current_size++;
}

void process_table_deletevp(Process_Table* pt,Process* p) {
  int pid = p->pid;
  free(pt->proc_arr[pid]);
  pt->proc_arr[pid] = NULL;
  pt->current_size--;
}
void process_table_delete(Process_Table* pt,int pid) {
  //Deletes based on a given process id
  assert(pid<MAX_SIZE_PROCESS_TABLE);
  free(pt->proc_arr[pid]);
  pt->proc_arr[pid] = NULL;
  pt->current_size--;
}
Process* process_table_pop(Process_Table* pt,int pid) {
  //Deletes based on a given process id
  assert(pid<MAX_SIZE_PROCESS_TABLE);
  Process *p = pt->proc_arr[pid];
  pt->proc_arr[pid] = NULL;
  int i;
  for(i=pid;i<pt->current_size;i++) {
    pt->proc_arr[i] = pt->proc_arr[i+1];
  }
  pt->current_size--;
  return p;
}
