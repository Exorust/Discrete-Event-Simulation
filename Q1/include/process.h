#ifndef PROCESS
#define PROCESS

#define MAX_SIZE_PROCESS_TABLE 1024

//TODO Add more states?
typedef enum Process_Type_t {
  PREADY,
  PRUNNING
}Process_Type;

typedef struct Process_t {
int pid;
Process_Type state;
int arrival_time;
int cpu_burst;
int wait_time;
char* scheduling_policy;
int time_quantum;
int preemption;
// add other fields which you feel are necessary
} Process;



//Function Declarations
Process* process_initialize(int,int);
void process_print(Process *);

#endif
