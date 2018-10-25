// #include"include/event_queue.h"
// #include"include/process_table.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[]) {
  FILE * fp;
  fp = fopen("process.csv", "r");
  int arrt,burst;
  do {
    fscanf(fp,"%d,%d", &arrt, &burst);
  } while(!feof(fp));
  fclose(fp);
  return 0;
}
