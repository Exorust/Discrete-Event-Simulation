#ifndef PROCESS_TABLE
#define PROCESS_TABLE

#define MAX_SIZE_PROCESS_TABLE 1024

typedef struct Process {
int pid;
char state;
int arrival_time;
int cpu_burst;
int wait_time;
char* scheduling_policy;
int time_quantum;
int preemption;
// add other fields which you feel are necessary
} Process;

typedef struct Process_Table_t {
  int current_size; // Total number of processes in the array
  Process* proc_arr[MAX_SIZE_PROCESS_TABLE];   //Contains pointers to the respective process
} Process_Table;

//Function Declarations
Process* process_initialize(int,int);
Process_Table* process_table_initialize();
int process_table_full(Process_Table*);
void process_table_add(Process_Table*,Process*);
void process_table_deletevp(Process_Table* ,Process*);
void process_table_delete(Process_Table*,int);


#endif
