#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(){
    const char* fifoName = "./myPipe1";
    int fd = open(fifoName, O_RDONLY);
    int num;

    while(read(fd, &num, sizeof(num)) > 0){
        printf("Read: %i\n", num);
    }
    close(fd);
    unlink(fifoName);
    return 0;
}