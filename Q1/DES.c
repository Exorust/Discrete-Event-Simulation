#include "include/event.h"
#include "include/ready_queue_FCFS.h"
#include "include/process_table.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define IDLE -1
#define RR 1
#define FCFS 2

int main(int argc, char const *argv[]) {
  int CPU; // Contains the value of the running process
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
  int CPU = -1;
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
        Event* e = ready_queue_FCFS_pop(rq);
        switch (e->type) {
          case EDEFAULT: {
            print_event(e);
            break;
          }
          case EARRIVAL: {
            if(CPU == IDLE ) {
              //Idle run it

            }
            else {
              //Not idle add to ready_queue

            }
            break;
          }
          case ECPUBURSTCOMPLETION: {

            break;
          }
          case ETIMEREXPIRED: {
            //This is not possible here.
            abort(void)
            break;
          }
          default {
            //Incase of failure
            abort(void);
          }

        }


      }

      break;
    }
    case 2: {
      // Multilevel Feedback Queue
      Ready_Queue_FCFS* rq_f = ready_queue_FCFS_initialize();
      Ready_Queue_RR* rq_r = ready_queue_RR_initialize();
      int i;
      for(i=0;i<pt_input->current_size;i++) {
        if((pt_input->proc_arr)[i]->time <= CPUtime) {
          Process* p = process_table_pop(pt_input,i);
          Event* e = event_initialize_process(CPUtime,p);
          //If less than 8 sec add to rr or else in fcfs
          if(p->cpu_burst <= 8){
            ready_queue_RR_push(rq_r,e)
          }
          else {
            ready_queue_FCFS_push(rq_f,e);
          }
        }
      }
      while(ready_queue_FCFS_size(rq_f) != 0 && ready_queue_RR_size(rq_r) != 0){
        for(i=0;i<pt_input->current_size;i++) {
          if((pt_input->proc_arr)[i]->time <= CPUtime) {
            Process* p = process_table_pop(pt_input,i);
            Event* e = event_initialize_process(CPUtime,p);
            //If less than 8 sec add to rr or else in fcfs
            if(p->cpu_burst <= 8){
              ready_queue_RR_push(rq_r,e)
            }
            else {
              ready_queue_FCFS_push(rq_f,e);
            }
          }
        }
        // The event that is first in the rr, if rr empty then fcfs
        int queue_type = -1;     // Type of queue from which it is taken. 1-> RR, 2-> FCFS
        if(ready_queue_RR_size(rq_r) != 0){
          Event* e = ready_queue_RR_pop(rq_r);
          queue_type = 1;
        }
        else if ( ready_queue_RR_size(rq_r) == 0 && ready_queue_FCFS_size(rq_f) != 0) {
          Event* e = ready_queue_FCFS_pop(rq_f);
          queue_type = 2;
        }
        else {
          // Both cant be zero here.
          abort(void);
        }
        switch (queue_type) {
          case RR: {
            switch (e->type) {
              case EDEFAULT: {
                print_event(e);
                break;
              }
              case EARRIVAL: {
                if(CPU == IDLE ) {
                  //Idle run it

                }
                else {
                  //Not idle add to ready_queue

                }
                break;
              }
              case ECPUBURSTCOMPLETION: {

                break;
              }
              case ETIMEREXPIRED: {
                //This is not possible here.
                abort(void)
                break;
              }
              default {
                //Incase of failure
                abort(void);
              }
            }
          }
            break;
          case FCFS: {
            switch (e->type) {
              case EDEFAULT: {
                print_event(e);
                break;
              }
              case EARRIVAL: {
                if(CPU == IDLE ) {
                  //Idle run it

                }
                else {
                  //Not idle add to ready_queue

                }
                break;
              }
              case ECPUBURSTCOMPLETION: {

                break;
              }
              case ETIMEREXPIRED: {
                //This is not possible here.
                abort(void)
                break;
              }
              default {
                //Incase of failure
                abort(void);
              }
            }
            break;
          }
        }
        //Finish the Multiqueue while
      }
      // Break from the Multiqueue section
      break;
    }
    default: {
      printf("ERROR\n" );
      abort(void);
      break;
    }
  }

  sum = 0;
  total = pt->current_size;
  while(pt->current_size != 0) {
      Process* p = process_table_pop(pt,0);
      if(p != NULL) {
        sum += p->wait_time
      }
  }
  double awt = sum/total;
  printf("\nAWT: %f\n", awt );

  return 0;
}
