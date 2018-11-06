#include "include/event.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

Event* event_initialize(double inp_time) {
  Event* e = (Event*)malloc(sizeof(Event));
  e->time = inp_time;
  return e;
}
