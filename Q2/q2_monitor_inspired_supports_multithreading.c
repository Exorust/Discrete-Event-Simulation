#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<limits.h>
#include<semaphore.h>
#include<pthread.h>

#define _GNU_SOURCE
#define true 1
#define false 0
#define bool int
#define A 0
#define B 1
#define C 2
#define D 3



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
int runningProcessInstance[8] = {false};

long long thresholds[4] = {0};

pthread_mutex_t mutexForProcesses;


typedef struct parameters
{
	int k;
	int processType;
}params;


/* 
    mutex based solution:
    ---------------------
    The solution is an extension to the dining philosopher problem where both forks are necessarily picked up 
    to eat. 
    1. Exactly one process at a time is allowed from the 8*k process requesting.
    2. It uses a system inspired by malloc and free functions where the functions resAlloc and resRelease 
        are used to allocate and reclaim resources with the corresponding probabilities. 
    3. If it can't find the resource it needs, it exits because there is a resource underflow.
*/

// bitwise operators for collection of resources: A,B,C,D,E. NOT NEEDED APPARENTLY, just quit program saying resource underflow


bool resAlloc(int neededA,int neededB, int neededC, int neededD){

// Process Resources
// 1        A, B, C
// 2        B, C, D
// 3        A, C, D
// 4        A, B, D
// 5        A
// 6        B
// 7        C
// 8        D
    if(neededA == true && resource_qantity[A] > 0){
        resource_qantity[A]--;
	}
    else if(resource_qantity[A] <= 0 && neededA && (runningProcessInstance[0] || runningProcessInstance[2] || runningProcessInstance[3] || runningProcessInstance[4])){
    	while((runningProcessInstance[0] || runningProcessInstance[2] || runningProcessInstance[3] || runningProcessInstance[4])){
    		pthread_mutex_lock(&mutexForProcesses);
    		puts("A");
    		if(resource_qantity[A] > 0){
    			resource_qantity[A] --; 
    			pthread_mutex_unlock(&mutexForProcesses);
    			return INT_MAX;
    		}
    		pthread_mutex_unlock(&mutexForProcesses);
    	    pthread_yield();
        }
		// pthread_mutex_unlock(&mutexForProcesses);
		return A;
    	
    }
    else if(resource_qantity[A] <= 0){
        return A;
    }
    if(neededB == true && resource_qantity[B] > 0){
        resource_qantity[B]--;
    }
    else if(resource_qantity[B] <= 0 && neededB && (runningProcessInstance[0] || runningProcessInstance[1] || runningProcessInstance[3] || runningProcessInstance[5])){
    	// wait
    	while((runningProcessInstance[0] || runningProcessInstance[1] || runningProcessInstance[3] || runningProcessInstance[5])){
    		pthread_mutex_lock(&mutexForProcesses);
    		puts("B");
    		if(resource_qantity[B] > 0){
    			resource_qantity[B] --; 
    			pthread_mutex_unlock(&mutexForProcesses);
    			return INT_MAX;
    		}
    		pthread_mutex_unlock(&mutexForProcesses);
            pthread_yield();
    	}
		// pthread_mutex_unlock(&mutexForProcesses);
		return B;
    }
    else if(resource_qantity[B] <= 0){
        return B;
    }
    if(neededC == true && resource_qantity[C] > 0){
        resource_qantity[C]--;
    }
    else if(resource_qantity[C] <= 0 && neededC && (runningProcessInstance[0] || runningProcessInstance[1] || runningProcessInstance[2] || runningProcessInstance[6])){
    	// wait
    	while((runningProcessInstance[0] || runningProcessInstance[2] || runningProcessInstance[3] || runningProcessInstance[4])){
    		pthread_mutex_lock(&mutexForProcesses);
    		puts("C");
    		if(resource_qantity[C] > 0){
    			resource_qantity[C] --; 
    			pthread_mutex_unlock(&mutexForProcesses);
    			return INT_MAX;
    		}
    		pthread_mutex_unlock(&mutexForProcesses);
            pthread_yield();
    	}
		// pthread_mutex_unlock(&mutexForProcesses);
		return C;
    }
    else if(resource_qantity[C] <= 0){
        return C;
    }
    if(neededD == true && resource_qantity[D] > 0){
        resource_qantity[D]--;
    }
    else if(resource_qantity[D] <= 0 && neededD && (runningProcessInstance[1] || runningProcessInstance[2] || runningProcessInstance[3] || runningProcessInstance[7])){
    	// wait
    	while((runningProcessInstance[1] || runningProcessInstance[2] || runningProcessInstance[3] || runningProcessInstance[7])){
    		pthread_mutex_lock(&mutexForProcesses);
    		puts("D");
    		if(resource_qantity[D] > 0){
    			resource_qantity[D] --; 
    			pthread_mutex_unlock(&mutexForProcesses);
    			return INT_MAX;
    		}
    		pthread_mutex_unlock(&mutexForProcesses);
            pthread_yield();
    	}
		return D;
    }
    else if(resource_qantity[D] <= 0){
        return D;
    }
    return INT_MAX;
}

bool resRelease(int releaseA,int releaseB, int releaseC, int releaseD){
    // Resource Probability of Collection
    // A            2/3
    // B            3/4
    // C            3/5
    // D            2/3
    int randA,randB,randC,randD;
    randA = rand();
    randB = rand();
    randC = rand();
    randD = rand();

    printf("A: %d B: %d C: %d D: %d\n",resource_qantity[A],resource_qantity[B],resource_qantity[C],resource_qantity[D]);

    if(releaseA && randA < thresholds[A]){
        resource_qantity[A]++;
        puts("A collected");
    }
    if(releaseB && randB < thresholds[B]){
        resource_qantity[B]++;
        puts("B collected");
    }
    if(releaseC && randC < thresholds[C]){
        resource_qantity[C]++;
        puts("C collected");
    }
    if(releaseD && randD < thresholds[D]){
        resource_qantity[D]++;
        puts("D collected");
    }
    return true;
}

void thread_funciton(void* processParams){
	params* param = (params*) processParams;
	int i;
	int processType = param->processType;
    int k = param->k;
	switch(processType){
        case 0:
        for(i = 0; i < k; i++){
            pthread_mutex_lock(&mutexForProcesses);
            printf("\nProcess Entered: %d\n",processType+1);
            int res = resAlloc(true,true,true,false);
            if(res  == INT_MAX){
                printf("allocated resources to process %d\n",processType+1);
                pthread_mutex_unlock(&mutexForProcesses);
                pthread_yield();
				pthread_mutex_lock(&mutexForProcesses);
                puts("1: running");
            	runningProcessInstance[processType] = true;
                printf("finished %d\n\n",processType+1);
                int hasReleased = resRelease(true,true,true,false);
                pthread_mutex_unlock(&mutexForProcesses);
                runningProcessInstance[processType] = false;
                pthread_yield();
            }
            else{
                char resourceUnderflow[] = "ABCD";
                printf("Resource Underflow Process %d %c\n",processType,resourceUnderflow[res]);
                exit(0);
            }
            
        }
        break;
        
        case 1:
        for(i = 0; i < k; i++){
            pthread_mutex_lock(&mutexForProcesses);
            printf("\nProcess Entered: %d\n",processType+1);
            int res = resAlloc(false,true,true,true);
            if(res  == INT_MAX){
                printf("allocated resources to process %d\n",processType+1);
                pthread_mutex_unlock(&mutexForProcesses);
                pthread_yield();
				pthread_mutex_lock(&mutexForProcesses);
                puts("2: running");
            	runningProcessInstance[processType] = true;
                printf("finished %d\n\n",processType+1);
                int hasReleased = resRelease(false,true,true,true);
                pthread_mutex_unlock(&mutexForProcesses);
                runningProcessInstance[processType] = false;
                pthread_yield();
            }
            else{
                char resourceUnderflow[] = "ABCD";
                printf("Resource Underflow Process %d %c\n",processType,resourceUnderflow[res]);
                exit(0);
            }
            
        }

        break;
        
        case 2:
        for(i = 0; i < k; i++){
            pthread_mutex_lock(&mutexForProcesses);
            printf("\nProcess Entered: %d\n",processType+1);
            int res = resAlloc(true,false,true,true);
            if(res  == INT_MAX){
                printf("allocated resources to process %d\n",processType+1);
            	pthread_mutex_unlock(&mutexForProcesses);
            	pthread_yield();
				pthread_mutex_lock(&mutexForProcesses);
                puts("3: running");
            	runningProcessInstance[processType] = true;
                printf("finished %d\n\n",processType+1);
                int hasReleased = resRelease(true,false,true,true);
                pthread_mutex_unlock(&mutexForProcesses);
                runningProcessInstance[processType] = false;
                pthread_yield();
            }
            else{
                char resourceUnderflow[] = "ABCD";
                printf("Resource Underflow Process %d %c\n",processType,resourceUnderflow[res]);
                exit(0);
            }
            
        }
        break;
        
        case 3:
        for(i = 0; i < k; i++){
            pthread_mutex_lock(&mutexForProcesses);
            printf("\nProcess Entered: %d\n",processType+1);
            int res = resAlloc(true,true,false,true);
            if(res  == INT_MAX){
                printf("allocated resources to process %d\n",processType+1);
            	pthread_mutex_unlock(&mutexForProcesses);
            	pthread_yield();
				pthread_mutex_lock(&mutexForProcesses);
                puts("4: running");
            	runningProcessInstance[processType] = true;
                printf("finished %d\n\n",processType+1);
                int hasReleased = resRelease(true,true,false,true);
                pthread_mutex_unlock(&mutexForProcesses);
                runningProcessInstance[processType] = false;
                pthread_yield();
            }
            else{
                char resourceUnderflow[] = "ABCD";
                printf("Resource Underflow Process %d %c\n",processType,resourceUnderflow[res]);
                exit(0);
            }
            
        }

        break;
        
        case 4:
        for(i = 0; i < k; i++){
            pthread_mutex_lock(&mutexForProcesses);
            printf("\nProcess Entered: %d\n",processType+1);
            int res = resAlloc(true,false,false,false);
            if(res  == INT_MAX){
                printf("allocated resources to process %d\n",processType+1);
            	pthread_mutex_unlock(&mutexForProcesses);
            	pthread_yield();
				pthread_mutex_lock(&mutexForProcesses);
                puts("5: running");
            	runningProcessInstance[processType] = true;
                printf("finished process %d\n\n",processType+1);
                int hasReleased = resRelease(true,false,false,false);
                pthread_mutex_unlock(&mutexForProcesses);
                runningProcessInstance[processType] = false;
                pthread_yield();
            }
            else{
                char resourceUnderflow[] = "ABCD";
                printf("Resource Underflow Process %d %c\n",processType,resourceUnderflow[res]);
                exit(0);
            }
            
        }
        break;
        
        case 5:
        for(i = 0; i < k; i++){
            pthread_mutex_lock(&mutexForProcesses);
            printf("\nProcess Entered: %d\n",processType+1);
            int res = resAlloc(false,true,false,false);
            if(res  == INT_MAX){
                printf("allocated resources to process %d\n",processType+1);
            	pthread_mutex_unlock(&mutexForProcesses);
            	pthread_yield();
				pthread_mutex_lock(&mutexForProcesses);
                puts("6: running");
            	runningProcessInstance[processType] = true;
                printf("finished process %d\n\n",processType+1);
                int hasReleased = resRelease(false,true,false,false);
                pthread_mutex_unlock(&mutexForProcesses);
                runningProcessInstance[processType] = false;
                pthread_yield();
            }
            else{
                char resourceUnderflow[] = "ABCD";
                printf("Resource Underflow Process %d %c\n",processType,resourceUnderflow[res]);
                exit(0);
            }
            
        }
    
        break;
        
        case 6:
        for(i = 0; i < k; i++){
            pthread_mutex_lock(&mutexForProcesses);
            printf("\nProcess Entered: %d\n",processType+1);
            int res = resAlloc(false,false,true,false);
            if(res  == INT_MAX){
                printf("allocated resources to process %d\n",processType+1);
            	pthread_mutex_unlock(&mutexForProcesses);
            	pthread_yield();
				pthread_mutex_lock(&mutexForProcesses);
                puts("7: running");
            	runningProcessInstance[processType] = true;
                printf("finished process %d\n\n",processType+1);
                int hasReleased = resRelease(false,false,true,false);
                pthread_mutex_unlock(&mutexForProcesses);
                runningProcessInstance[processType] = false;
                pthread_yield();
            }
            else{
                char resourceUnderflow[] = "ABCD";
                printf("Resource Underflow Process %d %c\n",processType,resourceUnderflow[res]);
                exit(0);
            }
            
        }

        break;
        
        case 7:
        for(i = 0; i < k; i++){
            pthread_mutex_lock(&mutexForProcesses);
            printf("\nProcess Entered: %d\n",processType+1);
            int res = resAlloc(true,false,false,true);
            if(res  == INT_MAX){
                printf("allocated resources to process %d\n",processType+1);    
            	pthread_mutex_unlock(&mutexForProcesses);
            	pthread_yield();
				pthread_mutex_lock(&mutexForProcesses);
                puts("8: running");
            	runningProcessInstance[processType] = true;
                printf("finished process %d\n\n",processType+1);
                int hasReleased = resRelease(false,false,false,true);
                pthread_mutex_unlock(&mutexForProcesses);
                runningProcessInstance[processType] = false;
                pthread_yield();
            }
            else{
                char resourceUnderflow[] = "ABCD";
                printf("Resource Underflow Process %d %c\n",processType,resourceUnderflow[res]);
                exit(0);
            }
            
        }
        break;
    }
    pthread_exit(0);
}

int main(){
    // random values threshold for 
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
    // puts("lite");
    pthread_t processes[8];
    for(j = 0; j < 8; j++){
        // printf(": %d\n",j+1);
        params* parametersForThread = malloc(sizeof(params));
        parametersForThread->k = k;
        parametersForThread->processType = j;
        pthread_create(&processes[j],NULL,(void*)&thread_funciton,(void *)parametersForThread);
    }
    for(j = 0; j < 8; j++){
        pthread_join(processes[j],NULL);
    }
    // for(j = 0; j < 8; j++){
    //     printf("%d \n",runningProcessInstance[j]);;
    // }
    puts("\n main thread exiting");
    return 0;
}