#ifndef EVENT
#define EVENT

typedef enum Event_Type_t {
  Arrival,
  CPUburstCompletion,
  TimerExpired
}Event_Type;

typedef struct Event_t {
  Event_Type type;
  double time; // time units since the start of the simulation
  // add other fields which you feel are necessary
} Event;

#endif
