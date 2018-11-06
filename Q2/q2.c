#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<semaphore.h>
#include<pthread.h>

#define _GNU_SOURCE
#define true 1
#define false 0
#define bool int

// Process Resources
// 1        A, B, C
// 2        B, C, D
// 3        A, C, D
// 4        A, B, D
// 5        A
// 6        B
// 7        C
// 8        D

// Resource Probability of Collection
// A            2/3
// B            3/4
// C            3/5
// D            2/3


// Now, implement this synchronization problem using semaphores. You must ensure that:
// ● every process runs exactly k times;
// ● the same instance of a resource is not used by multiple processes at the same time;
// ● a process (say Process 4) can start again only if Process 4 is not already running;
// ● since there is only one CPU, more than 1 process cannot run simultaneously;
// ● deadlocks don’t happen - say at a moment quantity of A - 1, B - 1, C - 1, D - 1 and Process
// 1 acquires lock on A, 2 on B, D and 3 on C => deadlock.

// Input:
// k it reincarnated k times
// a b c d
// First line contains ‘k’, the number of times each process should run.
// Next line contains a, b, c, d, the initial quantity of the resources.

// Output:
// On the console, you must print
// ● the resources (A/B/C/D) every time they get collected,
// ● when a process starts
// ● when the process is running,
// ● and when it finishes, the resources it is waiting upon.
// You must print this information sequentially as and when it happens.


int k;
int resource_qantity[4] = {0};  // shared resource
int lastProcess;                // shared variable between OS and process
int** finishedProcesses;        // stack for process recollection
int finishedProcessInstance[8] = {__INT_MAX__};
int processFinishedCount = 0;   // OS needs to run at least these many times for garbage collection

long long thresholds[4] = {0};

pthread_mutex_t mutexForProcesses;
pthread_mutex_t mutexBetweenOsAndProcess;

/* 
    Two layered structure for processes:
    --------------------------------------
    first layer: mutex for selecting a processes,
    second layer: mutex for acquiring a resource between the OS thread and the process
    Expected invariant: OS waits until it a process terminates

*/

// bitwise operators for collection of resources: A,B,C,D,E.

void os_function(void* args){
    // sleep(2);

    // Process Resources
    // 1        A, B, C
    // 2        B, C, D
    // 3        A, C, D
    // 4        A, B, D
    // 5        A
    // 6        B
    // 7        C
    // 8        D

    // Resource Probability of Collection
    // A            2/3
    // B            3/4
    // C            3/5
    // D            2/3
    
    puts("\n\nwaiting....");
    while(processFinishedCount <= 8*k){
        pthread_mutex_lock(&mutexBetweenOsAndProcess);
            puts("checking laude ");
            processFinishedCount++;
        // pop each process from the finishedProcesses array
        if(finishedProcessInstance[0] > 0){
            long long randomNumberA = (long long)rand();
            long long randomNumberB = (long long)rand();
            long long randomNumberC = (long long)rand();
            printf(" number %lld\n",randomNumber);
            if (randomNumberA < thresholds[0]){}
            if (randomNumberB < thresholds[1]){}
            if (randomNumberC < thresholds[2]){}
        }
        if(finishedProcessInstance[1] > 0){
            long long randomNumberB = (long long)rand();
            long long randomNumberC = (long long)rand();
            long long randomNumberD = (long long)rand();
            printf(" number %lld\n",randomNumber);
            if (randomNumberB < thresholds[2]){}
            if (randomNumberC < thresholds[2]){}
            if (randomNumberD < thresholds[2]){}
        }
        if(finishedProcessInstance[2] > 0){
            long long randomNumber = (long long)rand();
            printf(" number %lld\n",randomNumber);
        }
        if(finishedProcessInstance[3] > 0){
            long long randomNumber = (long long)rand();
            printf(" number %lld\n",randomNumber);
        }
        if(finishedProcessInstance[4] > 0){
            long long randomNumber = (long long)rand();
            printf(" number %lld\n",randomNumber);
        }
        if(finishedProcessInstance[5] > 0){
            long long randomNumber = (long long)rand();
            printf(" number %lld\n",randomNumber);
        }
        if(finishedProcessInstance[6] > 0){
            long long randomNumber = (long long)rand();
            printf(" number %lld\n",randomNumber);
        }
        if(finishedProcessInstance[7] > 0){
            long long randomNumber = (long long)rand();
            printf(" number %lld\n",randomNumber);
        }

        pthread_mutex_unlock(&mutexBetweenOsAndProcess);
    }
    puts("\n\nkhatam laude");
    pthread_mutex_unlock(&mutexBetweenOsAndProcess);
    int  res = pthread_yield();
}

void thread_funciton(void* process){
        int processNumber = *(int*)process;
        int res;
    pthread_yield();
// 1        A, B, C
// 2        B, C, D
// 3        A, C, D
// 4        A, B, D
// 5        A
// 6        B
// 7        C
// 8        D
        // printf("proc %d\n",processNumber);
        switch(processNumber){

            case 0:
                while(1){
                    pthread_mutex_lock(&mutexForProcesses);
                    pthread_mutex_lock(&mutexBetweenOsAndProcess);
                    // puts("lite 1");
                    if(resource_qantity[0] >= 1 && resource_qantity[1] >= 1 && resource_qantity[2] >= 1){
                        puts("\nmil gaya 1");
                        finishedProcesses[0][finishedProcessInstance[0]++] = 0;
                        resource_qantity[0]--;
                        resource_qantity[1]--;
                        resource_qantity[2]--;
                        processFinishedCount++;
                        pthread_mutex_unlock(&mutexBetweenOsAndProcess);
                        pthread_mutex_unlock(&mutexForProcesses);
                        break;
                    }

                    else{
                        // puts("\nnahi mila\n"); 
                        pthread_mutex_unlock(&mutexBetweenOsAndProcess);
                        pthread_mutex_unlock(&mutexForProcesses);
                        res = pthread_yield(); 
                        // break;
                    }

                    // res = pthread_yield();
                    // printf("res %d ",res);
                    // pthread_exit(0);
                }
                puts("not lite 1");

            break;
            
            case 1:
                while(1){
                    pthread_mutex_lock(&mutexForProcesses);
                    pthread_mutex_lock(&mutexBetweenOsAndProcess);
                    // puts("lite 2");
                    processFinishedCount++;
                    // sleep(2);
                    if(resource_qantity[1] > 1 && resource_qantity[2] > 1 && resource_qantity[3] > 1){
                            puts("\nmil gaya 2\n");
                            finishedProcesses[1][finishedProcessInstance[1]++] = 0;
                            resource_qantity[1]--;
                            resource_qantity[2]--;
                            resource_qantity[3]--;
                            pthread_mutex_unlock(&mutexBetweenOsAndProcess);
                            pthread_mutex_unlock(&mutexForProcesses);                            
                            break;
                        }

                        else{
                            // puts("nahi mila"); 
                            pthread_mutex_unlock(&mutexBetweenOsAndProcess);
                            pthread_mutex_unlock(&mutexForProcesses);
                            res = pthread_yield(); 
                            // // res = pthread_yield();
                            // break;
                        }
                    // printf("res %d ",res);
                    // pthread_exit(0);
                }
                puts("not lite 2");
            break;
            
            case 2:
                while(1){
                    pthread_mutex_lock(&mutexForProcesses);
                    pthread_mutex_lock(&mutexBetweenOsAndProcess);
                    // puts("lite 3");
                    processFinishedCount++;
                    // sleep(3);
                    if(resource_qantity[0] >= 1 && resource_qantity[2] >= 1 && resource_qantity[3] >= 1){
                        puts("\nmil gaya 3\n");
                        resource_qantity[0]--;
                        resource_qantity[2]--;
                        resource_qantity[3]--;
                        finishedProcesses[2][finishedProcessInstance[2]++] = 0;
                        pthread_mutex_unlock(&mutexBetweenOsAndProcess);
                        pthread_mutex_unlock(&mutexForProcesses);
                        // res = pthread_yield();
                        break;
                    }

                    else{
                        // puts("\nnahi mila\n"); 
                        pthread_mutex_unlock(&mutexBetweenOsAndProcess);
                        pthread_mutex_unlock(&mutexForProcesses);
                        res = pthread_yield(); 
                        // break;
                    }
                    // printf("res %d ",res);
                    // pthread_exit(0);
                }
                puts("not lite 3");
                    
            break;
            
            case 3:
                while(1){
                    pthread_mutex_lock(&mutexForProcesses);
                    pthread_mutex_lock(&mutexBetweenOsAndProcess);
                    // puts("lite 4");
                    processFinishedCount++;
                    // sleep(4);
                    if(resource_qantity[0] >= 1 && resource_qantity[1] >= 1 && resource_qantity[3] >= 1){
                        puts("\nmil gaya 4\n");
                        finishedProcesses[3][finishedProcessInstance[3]++] = 0;
                        resource_qantity[0]--;
                        resource_qantity[1]--;
                        resource_qantity[3]--;
                        pthread_mutex_unlock(&mutexBetweenOsAndProcess);
                        pthread_mutex_unlock(&mutexForProcesses);
                        // res = pthread_yield();
                        break;
                    }

                    else{
                        // puts("\nnahi mila\n"); 
                        pthread_mutex_unlock(&mutexBetweenOsAndProcess);
                        pthread_mutex_unlock(&mutexForProcesses);
                        res = pthread_yield(); 
                        // break;
                    }
                    // printf("res %d ",res);
                    // pthread_exit(0);
                }
                puts("not lite 4");
                
            break;
            
            case 4:
                while(1){
                    pthread_mutex_lock(&mutexForProcesses);
                    pthread_mutex_lock(&mutexBetweenOsAndProcess);
                    // puts("lite 5");
                    processFinishedCount++;
                    // sleep(5);
                    if(resource_qantity[0] >= 1){
                        puts("\nmil gaya 5 \n");
                        resource_qantity[0]--;
                        finishedProcesses[4][finishedProcessInstance[4]++] = 0;
                        pthread_mutex_unlock(&mutexBetweenOsAndProcess);
                        pthread_mutex_unlock(&mutexForProcesses);
                        // res = pthread_yield();
                        break;
                    }

                    else{
                        // puts("\nnahi mila\n"); 
                        pthread_mutex_unlock(&mutexBetweenOsAndProcess);
                        pthread_mutex_unlock(&mutexForProcesses);
                        res = pthread_yield(); 
                        // break;
                    }
                    // printf("res %d ",res);
                    // pthread_exit(0);
                }
                puts("not lite 5");
                
            break;
            
            case 5:
                while(1){
                    pthread_mutex_lock(&mutexForProcesses);
                    pthread_mutex_lock(&mutexBetweenOsAndProcess);
                    // puts("lite 6");
                    processFinishedCount++;
                    // sleep(4);
                    if( resource_qantity[1] >= 1){
                        puts("\nmil gaya 6\n");
                        finishedProcesses[5][finishedProcessInstance[5]++] = 0;
                        resource_qantity[1]--;
                        pthread_mutex_unlock(&mutexBetweenOsAndProcess);
                        pthread_mutex_unlock(&mutexForProcesses);
                        // res = pthread_yield();
                        break;
                    }

                    else{
                        // puts("\nnahi mila\n"); 
                        pthread_mutex_unlock(&mutexBetweenOsAndProcess);
                        pthread_mutex_unlock(&mutexForProcesses);
                        res = pthread_yield(); 
                        // break;
                    }
                    
                    // printf("res %d ",res);
                    // pthread_exit(0);
                }
                puts("not lite 6");
                
            break;
            
            case 6:
                while(1){
                    pthread_mutex_lock(&mutexForProcesses);
                    pthread_mutex_lock(&mutexBetweenOsAndProcess);
                    // puts("lite 7");
                    processFinishedCount++;
                    // sleep(3);
                    if(resource_qantity[2] >= 1){
                        puts("\nmil gaya 7\n");
                        resource_qantity[2]--;
                        finishedProcesses[6][finishedProcessInstance[6]++] = 0;
                        pthread_mutex_unlock(&mutexBetweenOsAndProcess);
                        pthread_mutex_unlock(&mutexForProcesses);
                        // res = pthread_yield();
                        break;
                    }

                    else{
                        // puts("\nnahi mila\n"); 
                        pthread_mutex_unlock(&mutexBetweenOsAndProcess);
                        pthread_mutex_unlock(&mutexForProcesses);
                        res = pthread_yield();
                        // break; 
                    }
                    
                    // printf("res %d ",res);
                    // pthread_exit(0);
                }
                puts("not lite 7");
                
            break;
            
            case 7:
                while(1){
                    pthread_mutex_lock(&mutexForProcesses);
                    pthread_mutex_lock(&mutexBetweenOsAndProcess);
                    // puts("lite 8");
                    processFinishedCount++;
                    // sleep(2);
                    if(resource_qantity[3] >= 1){
                        puts("\nmil gaya 8\n");
                        resource_qantity[3]--;
                        finishedProcesses[7][finishedProcessInstance[7]++] = 0;
                        pthread_mutex_unlock(&mutexBetweenOsAndProcess);
                        pthread_mutex_unlock(&mutexForProcesses);
                        // res = pthread_yield();    
                        break;
                    }

                    else{
                        // puts("\nnahi mila\n"); 
                        pthread_mutex_unlock(&mutexBetweenOsAndProcess);
                        pthread_mutex_unlock(&mutexForProcesses);
                        res = pthread_yield(); 
                        // break;
                    }
                    // printf("res %d ",res);
                    // pthread_exit(0);
                }
                puts("not lite 8");

            break;

            default:
            puts("Invalid process number found, exiting");
            pthread_exit(0);
        };
        puts("thread finished");
        // pthread_mutex_unlock(&mutexBetweenOsAndProcess);
        pthread_exit(0);
     
}

int main(){
    thresholds[0] = 2*(long long)(RAND_MAX/3);
    thresholds[1] = 3*(long long)(RAND_MAX/4);
    thresholds[2] = 3*(long long)(RAND_MAX/5);
    thresholds[3] = 2*(long long)(RAND_MAX/3);
    puts("enter k");
    scanf("%d",&k);
    puts("enter resources");
    int i,j;
    for(i = 0; i < 4; i++){
        scanf("%d",&resource_qantity[i]);
        if(resource_qantity[i] <= 0){
            puts("solution not possible");
            return 1;
        }
    }
    finishedProcesses = malloc(8*sizeof(int*));
    for(i = 0; i < 8;i++){
        finishedProcesses[i] = malloc(k*sizeof(int));
        finishedProcessInstance[i] = 0;
    }
    puts("lite");
    pthread_t processes[8*k],osThread;

    // create 8*k processes
    for(i = 0; i < k; i++)  
        for(j = 0; j < 8; j++){
            printf("j: %d\n",j);
            pthread_create(&processes[8*i + j],NULL,(void*)&thread_funciton,(void*)&j);
        }

    pthread_create(&osThread,NULL,(void*)&os_function,(void*)0);

    for(i = 0; i < 8; i++){
        for(j = 0; j < k; j++){
            printf(" %d ",finishedProcesses[i][j]);
        }
        puts("");
    }

    for(i = 0; i < k; i++)  
        for(j = 0; j < 8; j++){
            pthread_join(processes[8*i + j],NULL);
        }
    pthread_join(osThread,NULL);

    puts("\n main thread exiting");
    return 0;
}