#ifndef EVENT_QUEUE
#define EVENT_QUEUE

#define MAX_SIZE_EVENT_QUEUE 1024

typedef struct Event_t {
enum eventType { Arrival, CPUburstCompletion, TimerExpired };
double time; // time units since the start of the simulation
// add other fields which you feel are necessary
} Event;

typedef struct Event_Queue_t {
  int current_size;
  Event* heap[MAX_SIZE_EVENT_QUEUE]; //Array of pointers to the event queue array
} Event_Queue;

#endif
