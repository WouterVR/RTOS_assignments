#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int program(){
    int value = 0;
    int i;
    pid_t pid = getpid();
    for(i=1; i<5; ++i){
        value += 1;
        printf("My very own PID is %d and the value I print is: %d \n", pid, value);
    }
}

int main() {
    fork();
    fork();
    program();
    return 0;
}