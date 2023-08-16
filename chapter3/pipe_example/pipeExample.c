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
    int pipeFDs[2];  // pipe file descriptors
    char buf;        // 1-byte buffer
    const char* msg = "This is the winter of our discontent\n";

    if (pipe(pipeFDs) < 0) report_and_die("pipe(...)");

    pid_t cpid = fork();
    if (cpid < 0) report_and_die("fork(...)");

    /*** child ***/
    if (0 == cpid) {
        close(pipeFDs[WriteEnd]);
        while (read(pipeFDs[ReadEnd], &buf, 1) > 0){
            write(STDOUT_FILENO, &buf, sizeof(buf));
        }
        close(pipeFDs[ReadEnd]);
        _exit(0);
    }
    /*** parent ***/
    else {
        close(pipeFDs[ReadEnd]);
        write(pipeFDs[WriteEnd], msg, strlen(msg));
        close(pipeFDs[WriteEnd]);  // generates an EOF
        wait(0);  // wait for child to exit
        exit(0);
    }
    return 0;
}