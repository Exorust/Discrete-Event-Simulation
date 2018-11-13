#! /bin/bash
gcc -g include/event.h include/ready_queue_FCFS.h include/ready_queue_RR.h include/process_table.h include/process.h include/event_heap.h;
gcc -g event.c event_heap.c process.c ready_queue_RR.c ready_queue_FCFS.c process_table.c DES.c -o DES.out;
echo "Program has compiled succesfully";
