#! /bin/bash
gcc -g include/event.h include/ready_queue_FCFS.h include/process_table.h  event.c ready_queue_FCFS.c process_table.c DES.c -o DES.out;
echo "Program has compiled succesfully";
