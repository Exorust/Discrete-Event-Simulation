#include "include/event.h"
#include "process_table.h"
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
Event* event_initialize(int inp_time, Process* p) {
  Event* e = (Event*)malloc(sizeof(Event));
  e->time = inp_time;
  e->p = p;
  return e;
}
