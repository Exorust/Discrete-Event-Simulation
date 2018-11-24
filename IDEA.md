IDEA
======

Listing of the DES components and model

Model:
---------------
System Entities: Processes & CPU
System Events: Process Completion
Events: default case, arrival case, cpu burst, timer expiration
System States: Number of Process Bursts in the Queue, CPU state
Random Variables: Arrival Time, CPU burst timing


EDIT TO IDEA

Add from pt_input to event, event to event queue
while (heap not empty) {
  0. Add from pt_input (pop) to event, event to event queue
  1. extract an Event from the heap;
  2. update time to match the Event;
  3. switch (type of Event) {
    process this event, possibly adding new Events to the heap;
  } // switch
  4. Update ready Queue??
} // while
