#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

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
    const char * greeting = "Hello, world!";
    int len = strlen(greeting) + 1; // + 1 for string terminator '\0'
    key_t key = 9876;

    char* mem_ptr = setup(key, len, IPC_CREAT | 0666);
    memcpy(mem_ptr, greeting, len);  // copy greeting to shared memory

    // wait for the other process to change the first char
    while (*mem_ptr == 'H') {
        sleep(1);
    }

    printf("%s is the new msg. putter existing...\n");
    return 0;
}