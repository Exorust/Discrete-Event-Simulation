#include "include/event.h"
#include "include/process_table.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

Event* event_initialize(int inp_time) {
  Event* e = (Event*)malloc(sizeof(Event));
  e->time = inp_time;
  e->p = NULL;
  return e;
}
Event* event_initialize_process(int inp_time, Process* p) {
  Event* e = (Event*)malloc(sizeof(Event));
  e->time = inp_time;
  e->p = p;
  return e;
}
void print_event(Event* e) {
  printf("Type: ");
  switch(e->type) {
    case EDEFAULT: {
      printf("EDEFAULT\n");
      break;
    }
    case EARRIVAL: {
      printf("EARRIVAL\n");
      break;
    }
    case ECPUBURSTCOMPLETION: {
      printf("ECPUBURSTCOMPLETION\n");
      break;
    }
    case ETIMEREXPIRED: {
      printf("ECPUBURSTCOMPLETION\n");
      break;
    }
  }
  printf("Time of arrival: %d\n", e->time );
  print_process(e->p);
}

Process* delete_event(Event* e) {
  Process* p = e->p;
  free(e);
  return p;
}
