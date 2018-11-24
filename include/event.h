#ifndef EVENT_HEADER
#define EVENT_HEADER

#include "process.h"

typedef enum Event_Type_t {
  EDEFAULT,
  EARRIVAL,
  ECPUBURSTCOMPLETION,
  ETIMEREXPIRED,
  EFCFS
}Event_Type;

typedef struct Event_t {
  Event_Type type;
  int time; // time units since the start of the simulation
  Process* p;  // to be used in Arrival situation
} Event;

//Function Declarations
Event* event_initialize(int);
Event* event_initialize_process(int,Process*);
void print_event(Event* );
Process* delete_event(Event*);
Event* event_initialize_wot_time(Process* );

#endif
