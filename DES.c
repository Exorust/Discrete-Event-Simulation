#include "include/event.h"
#include "include/ready_queue_FCFS.h"
#include "include/process_table.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[]) {
  int CPU; // Contains the value of the running process
  FILE * fp;
  fp = fopen("process.csv", "r");
  int arrival_time,cpu_burst;
  //Stores input times in pt_input
  Process_Table* pt_input = process_table_initialize();
  do {
    fscanf(fp,"%d,%d", &arrival_time, &cpu_burst);
    Process* p = process_initialize(arrival_time,cpu_burst);
    process_table_add(pt_input,p);
  } while(!feof(fp));
  fclose(fp);

  //TIME FOR THE SIM
  int CPUtime=0;
  //Type of simulation 1-> FCFS 2->MFQ
  int sim_type = 0;
  printf("Input sim type: \n1.First Come First Serve (FCFS) \n2.Multilevel Feedback Queue\n");
  scanf("%d",&sim_type);

  return 0;
}
