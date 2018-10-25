#! /bin/bash
gcc -g include/event_queue.h include/process_table.h  event_queue.c process_table.c DES.c -o DES.out;
echo "Program has compiled succesfully";
