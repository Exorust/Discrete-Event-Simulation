#ifndef PROCESS_TABLE
#define PROCESS_TABLE

#include "process.h"

#define MAX_SIZE_PROCESS_TABLE 4096

typedef struct Process_Table_t {
  int current_size; // Total number of processes in the array
  Process* proc_arr[MAX_SIZE_PROCESS_TABLE];   //Contains pointers to the respective process
} Process_Table;

//Function Declarations
Process* process_table_pop(Process_Table* ,int );
Process_Table* process_table_initialize();
int process_table_full(Process_Table*);
void process_table_add(Process_Table*,Process*);
void process_table_deletevp(Process_Table* ,Process*);
void process_table_delete(Process_Table*,int);


#endif
