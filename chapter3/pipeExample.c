#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define ReadEnd 0
#define WriteEnd 1

void report_and_die(const char* msg) {
    perror(msg);
    exit(-1);
}

int main() {
    int pipeFileDescriptors[2];
    char buf;        // 1-byte buffer
    const char* msg = "This is the winter of our discontent\n";

    if (pipe(pipeFileDescriptors) < 0) report_and_die("pipe(...)");

    pid_t cpid = fork();
    if (cpid < 0) report_and_die("fork(...)");

    return 0;
}