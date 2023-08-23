#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>


void report_and_die(const char* msg) {
    perror(msg);
    exit(-1);
}


char* setup(key_t key, int byte_count, int flags) {
    // 1. get shared memory and its identifier
    // key: user-supplied key , flags: including access rights
    int mem_id = shmget(key, byte_count, flags); 
    if (mem_id < 0) {
        report_and_die("failed on shmget");
    } 

    // 2. attach memory segment to putter's address space
    // the return value is a pointer to the first byte that was allocated

    // let the system pick the address at which the shared memory is mapped 
    void * shmaddr = 0; 
    // no optional flags
    int shmflg = 0;     
    char* mem_ptr = shmat(mem_id, shmaddr, shmflg);    
    if (mem_ptr == (void*) -1) {
        report_and_die("Failed on shmat");
    }
    return mem_ptr;
}

int main() {
    int len = 14;  // byte count of "Hello World!" with '\0' included
    key_t key = 9876;

    // attach memory segment to getter's address space
    char * mem_ptr = setup(key, len, 0666);
    *mem_ptr = 'h';
    puts(mem_ptr); 
    return 0;
}