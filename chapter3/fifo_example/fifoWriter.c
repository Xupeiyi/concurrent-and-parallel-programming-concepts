#include <fcntl.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#define MaxWrites 256

int main() {
    srand(time(0));
    const char * fifoName = "./myPipe1";
    mkfifo(fifoName, 0666);  // read/write for user/group/others
    int fd = open(fifoName, O_WRONLY);

    for (int i = 0; i < MaxWrites; i++) {
        int num = rand();
        write(fd, &num, sizeof(int));
        printf("Write: %d\n", num);
    }
    close(fd);
    unlink(fifoName);
    return 0;
}