#include "include/event_queue.h"
#include "include/process_table.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[]) {
  int CPU; // Contains the value of the running process
  FILE * fp;
  fp = fopen("process.csv", "r");
  int arrival_time,cpu_burst;
  Process_Table* pt = process_table_initialize();
  do {
    fscanf(fp,"%d,%d", &arrival_time, &cpu_burst);
    Process* p = process_initialize(arrival_time,cpu_burst);
    process_table_add(pt,p);
  } while(!feof(fp));
  fclose(fp);
  printf("Works");
  return 0;
}
