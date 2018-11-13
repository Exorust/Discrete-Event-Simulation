#include "include/event.h"
#include "include/ready_queue_FCFS.h"
#include "include/ready_queue_RR.h"
#include "include/process_table.h"
#include "include/process.h"
#include "include/event_heap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define IDLE -1
#define RR 1
#define FCFS 2

int main(int argc, char const *argv[]) {
  FILE * fp;
  fp = fopen("process.csv", "r");
  int time,cpu_burst;
  //Stores input times in pt_input
  Process_Table* pt_input = process_table_initialize();
  Process_Table* pt = process_table_initialize();
  do {
    fscanf(fp,"%d,%d", &time, &cpu_burst);
    Process* p = process_initialize(time,cpu_burst);
    process_table_add(pt_input,p);
  } while(!feof(fp));
  fclose(fp);

  //TIME FOR THE SIM
  int CPUtime=0;
  int CPU = -1; // Contains the value of the running process
  //Type of simulation 1-> FCFS 2->MFQ
  int sim_type = 0;
  printf("Input sim type: \n1.First Come First Serve (FCFS) \n2.Multilevel Feedback Queue\n");
  scanf("%d",&sim_type);

  switch (sim_type) {
    case 1: {
      //FCFS case
      // rq-> Ready Queue & pt -> Process Table
      Event_Heap* eh = event_heap_initialize();
      Ready_Queue_FCFS* rq = ready_queue_FCFS_initialize();
      int i;
      for(i=0;i<pt_input->current_size;i++) {
        if((pt_input->proc_arr)[i]->time <= CPUtime) {
          Process* p = process_table_pop(pt_input,i);
          Event* e = event_initialize_process(CPUtime,p);
          e->type = EARRIVAL;
          event_heap_push(eh,e);
        }
      }
      while(event_heap_size(eh) != 0){
        for(i=0;i<pt_input->current_size;i++) {
          if((pt_input->proc_arr)[i]->time <= CPUtime) {
            Process* p = process_table_pop(pt_input,i);
            Event* e = event_initialize_process(CPUtime,p);
            e->type = EARRIVAL;
            event_heap_push(eh,e);
          }
        }
        // The event that is first in the queue
        Event* e = event_heap_pop(eh);
        switch (e->type) {
          case EDEFAULT: {
            print_event(e);
            break;
          }
          case EARRIVAL: {
            process_table_add(pt,e->p);
            if(CPU == IDLE ) {
              //Idle run it
              e->p->wait_time = e->p->wait_time + (CPUtime - e->p->time);
              CPUtime += e->p->cpu_burst;
              Event* en = event_initialize_process(CPUtime,e->p);
              en->type = ECPUBURSTCOMPLETION;
              event_heap_push(eh,en);
            }
            else {
              //Not idle add to ready_queue
              e->p->state = PREADY;
              ready_queue_FCFS_push(rq,e->p);
            }
            break;
          }
          case ECPUBURSTCOMPLETION: {
            e->p->state = PFINISH;
            if(ready_queue_FCFS_size(rq) != 0) {
              Process* p = ready_queue_FCFS_pop(rq);
              p->wait_time = p->wait_time + (CPUtime - p->time);
              CPUtime += p->cpu_burst;
              Event* en = event_initialize_process(CPUtime,p);
              en->type = ECPUBURSTCOMPLETION;
              event_heap_push(eh,en);
            }
            break;
          }
          case ETIMEREXPIRED: {
            //This is not possible here.
            abort();
            break;
          }
          default: {
            //Incase of failure
            abort();
          }
          free(e);
        }


      }

      break;
    }
    case 2: {
      // Multilevel Feedback Queue

      // Break from the Multiqueue section
      break;
    }
    default: {
      printf("ERROR\n" );
      abort();
      break;
    }
  }

  int sum = 0,total;
  total = pt->current_size;
  while(pt->current_size != 0) {
      Process* p = process_table_pop(pt,0);
      if(p != NULL) {
        sum += p->wait_time;
      }
  }
  double awt = sum/total;
  printf("\nAWT: %f\n", awt );

  return 0;
}
