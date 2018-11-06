#include "process_table.h"

#ifndef EVENT
#define EVENT


typedef enum Event_Type_t {
  EARRIVAL,
  ECPUBURSTCOMPLETION,
  ETIMEREXPIRED
}Event_Type;

typedef struct Event_t {
  Event_Type type;
  int time; // time units since the start of the simulation
  Process* p  // to be used in Arrival situation
} Event;

//Function Declarations
Event* event_initialize(int);
Event* event_initialize(int,Process*);

#endif
