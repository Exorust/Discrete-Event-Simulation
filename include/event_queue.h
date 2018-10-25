#ifndef EVENT_QUEUE
#define EVENT_QUEUE

#define MAX_SIZE_EVENT_QUEUE 1024

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

typedef struct Event_Queue_t {
  int current_size; //Starts from 0, filled will be current_size-1
  Event* heap[MAX_SIZE_EVENT_QUEUE]; //Array of pointers to the event queue array
} Event_Queue;

//Function Declarations
Event* event_initialize(double);
Event_Queue* event_queue_initialize();
void event_queue_swap(Event_Queue*, int,int);
void event_queue_minheapify(Event_Queue*, int);
void event_queue_build_minheap (Event_Queue*);

#endif
