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
#define QUANTUM 4

int main(int argc, char const *argv[]) {
  FILE * fp;
  fp = fopen("process.csv", "r");
  int time,cpu_burst;
  //Stores input times in pt_input
  Process_Table* pt_input = process_table_initialize();
  Process_Table* pt = process_table_initialize();
  // int j = 0;
  while(!feof(fp)) {
    fscanf(fp,"%d,%d\n", &time, &cpu_burst);
    Process* p = process_initialize(time,cpu_burst);
    process_print(p);
    process_table_add(pt_input,p);
    // j++;
  }
  // printf("%d",j);
  fclose(fp);
  int i;

  // for(i=0;i<pt_input->current_size;i++) {
  //   process_print(pt->proc_arr[i]);
  // }

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
          Event* e = event_initialize_process(p->time,p);
          e->type = EARRIVAL;
          event_heap_push(eh,e);
        }
      }
      while(event_heap_size(eh) != 0){
        printf("\n\nWHILE LOOP\n" );
        printf("Size of Process_Table %d\n", pt_input->current_size );
        printf("ADDDING while CPUtime =%d\n",CPUtime );
        for(i=0;i<pt_input->current_size;i++) {
          if((pt_input->proc_arr)[i]->time <= CPUtime) {
            Process* p = process_table_pop(pt_input,i);
            i--;
            Event* e = event_initialize_process(p->time,p);
            e->type = EARRIVAL;
            event_heap_push(eh,e);
            printf("Size of Process_Table %d\n", pt_input->current_size );
            print_event(e);
          }
        }
        printf("==================\n" );
        // The event that is first in the queue
        Event* e = event_heap_pop(eh);
        // printf("%d",e->type);
        switch (e->type) {
          case EDEFAULT: {
            print_event(e);
            break;
          }
          case EARRIVAL: {
            print_event(e);
            process_table_add(pt,e->p);
            if(CPU == IDLE ) {
              //Idle run it
              e->p->wait_time = e->p->wait_time + (CPUtime - e->p->time);
              CPUtime += e->p->cpu_burst;
              Event* en = event_initialize_process(e->p->time,e->p);
              en->type = ECPUBURSTCOMPLETION;
              printf("Executed: ");
              print_event(en);
              event_heap_push(eh,en);
            }
            else {
              //Not idle add to ready_queue
              e->p->state = PREADY;
              ready_queue_FCFS_push(rq,e->p);
              printf("Ready Queue Push" );
              process_print(e->p);
            }
            break;
          }
          case ECPUBURSTCOMPLETION: {
            print_event(e);
            e->p->state = PFINISH;
            if(ready_queue_FCFS_size(rq) != 0) {
              Process* p = ready_queue_FCFS_pop(rq);
              p->wait_time = p->wait_time + (CPUtime - p->time);
              CPUtime += p->cpu_burst;
              Event* en = event_initialize_process(CPUtime,p);
              en->type = ECPUBURSTCOMPLETION;
              printf("Executed: ");
              print_event(en);
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
        }
        free(e);
      }
      break;
    }
    case 2: {
      // Multilevel Feedback Queue
      Event_Heap* eh = event_heap_initialize();
      Ready_Queue_FCFS* rq_f = ready_queue_FCFS_initialize();
      Ready_Queue_RR* rq_r = ready_queue_RR_initialize();
      int i;
      for(i=0;i<pt_input->current_size;i++) {
        if((pt_input->proc_arr)[i]->time <= CPUtime) {
          Process* p = process_table_pop(pt_input,i);
          Event* e = event_initialize_process(p->time,p);
          e->type = EARRIVAL;
          event_heap_push(eh,e);
        }
      }
      while(event_heap_size(eh) != 0){
        for(i=0;i<pt_input->current_size;i++) {
          if((pt_input->proc_arr)[i]->time <= CPUtime) {
            Process* p = process_table_pop(pt_input,i);
            Event* e = event_initialize_process(p->time,p);
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
            print_event(e);
            int queue_now;
            process_table_add(pt,e->p);
            if(e->p->cpu_burst <= 8) {
              //RR
              queue_now = RR;
              e->p->state = PREADY;
              ready_queue_RR_push(rq_r,e->p);
              printf(">RR\n" );
            }
            else {
              //FCFS
              queue_now = FCFS;
              e->p->state = PREADY;
              ready_queue_FCFS_push(rq_f,e->p);
              printf(">FCFS\n" );
            }
            if(CPU == IDLE) {
              if(ready_queue_RR_size(rq_r) != 0) {
                //RR
                printf("From RR\n" );
                Process* p = ready_queue_RR_pop(rq_r);
                process_print(p);
                if(p->cpu_burst <= QUANTUM) {
                  //Smaller than quantum
                  printf("Small\n" );
                  p->wait_time = p->wait_time + (CPUtime - p->time);
                  CPUtime += e->p->cpu_burst;
                  p->state = PFINISH;
                  Event* en = event_initialize_process(CPUtime,p);
                  en->type = ECPUBURSTCOMPLETION;
                  event_heap_push(eh,en);
                }
                else {
                  //1 QUANTUM
                  printf("1 Quantum\n" );
                  p->wait_time = p->wait_time + (CPUtime - p->time);
                  CPUtime += QUANTUM;
                  p->state = PREADY;
                  p->cpu_burst -= QUANTUM;
                  Event* en = event_initialize_process(CPUtime,p);
                  en->type = ETIMEREXPIRED;
                  event_heap_push(eh,en);
                }
              }
              else if(ready_queue_RR_size(rq_r) == 0 && ready_queue_FCFS_size(rq_f) != 0) {
                //FCFS
                printf("From FCFS\n" );
                Process* p = ready_queue_FCFS_pop(rq_f);
                process_print(p);
                p->wait_time = p->wait_time + (CPUtime - p->time);
                CPUtime += p->cpu_burst;
                p->state = PFINISH;
                Event* en = event_initialize_process(CPUtime,p);
                en->type = ECPUBURSTCOMPLETION;
                event_heap_push(eh,en);
              }
            }
            break;
          }
          case ECPUBURSTCOMPLETION: {
            print_event(e);
            e->p->state = PFINISH;
            if(CPU == IDLE) {
              if(ready_queue_RR_size(rq_r) != 0) {
                //RR
                printf("From RR\n" );
                Process* p = ready_queue_RR_pop(rq_r);
                process_print(p);
                if(p->cpu_burst <= QUANTUM) {
                  //Smaller than quantum
                  p->wait_time = p->wait_time + (CPUtime - p->time);
                  CPUtime += p->cpu_burst;
                  p->state = PFINISH;
                  Event* en = event_initialize_process(CPUtime,p);
                  en->type = ECPUBURSTCOMPLETION;
                  event_heap_push(eh,en);
                }
                else {
                  //1 QUANTUM
                  printf("1 Quantum\n" );
                  p->wait_time = p->wait_time + (CPUtime - p->time);
                  CPUtime += QUANTUM;
                  p->state = PREADY;
                  e->p->cpu_burst -= QUANTUM;
                  Event* en = event_initialize_process(CPUtime,e->p);
                  en->type = ETIMEREXPIRED;
                  event_heap_push(eh,en);
                }
              }
              else if(ready_queue_RR_size(rq_r) == 0 && ready_queue_FCFS_size(rq_f) != 0) {
                //FCFS
                printf("From FCFS\n" );
                Process* p = ready_queue_FCFS_pop(rq_f);
                process_print(p);
                p->wait_time = e->p->wait_time + (CPUtime - p->time);
                CPUtime += p->cpu_burst;
                p->state = PFINISH;
                Event* en = event_initialize_process(CPUtime,p);
                en->type = ECPUBURSTCOMPLETION;
                event_heap_push(eh,en);
              }
            }
            break;
          }
          case ETIMEREXPIRED: {
            print_event(e);
            e->p->state = PREADY;
            ready_queue_RR_push(rq_r,e->p);
            break;
          }
          default: {
            //Incase of failure
            abort();
          }
          free(e);
        }
      }
      // Break from the Multiqueue section
      break;
    }
    // End of case 2
  }

  float sum = 0,total = 0;
  total = pt->current_size;
  while(pt->current_size != 0) {
      Process* p = process_table_pop(pt,0);
      if(p != NULL) {
        printf("%d\n", p->wait_time );
        sum += p->wait_time;
      }
  }
  printf("%f %f\n", sum, total );
  float awt = sum/total;
  printf("\nAWT: %f\n", awt );

  return 0;
}
