#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h> 
#include <sys/resource.h>
#include <stdlib.h>

#define MAX_COUNT  10000
#define NUMOF_CHILDREN 12

int getProcessInformation(){
    pid_t pid = getpid();
    int niceValue = getpriority(PRIO_PROCESS, pid);
    double overflowumber=1;
    for(niceValue = -19; niceValue<20; niceValue++){
        overflowumber=1;   
        setpriority(PRIO_PROCESS, getpid(), niceValue);
        for(int i = 0; i<1000;i++){
            for(int j = 0; j<1000;j++){
                for(int k = 0; k<1000;k++){
                }
                
            } 
        }
        printf("*** child process %d has a nice value of: %d and the overflownumber is %f*** \n",pid, getpriority(PRIO_PROCESS, pid), overflowumber);
    }
    
    return 0;
}

int main(int argc, char *argv[]) {
    for(int i =0; i<argc; i++){
        printf("Commandline arguments are: %c \n", *argv[i]);
    }
    if(argc >=2){
        if(*argv[1]== 'n'){
            printf("input char is n \n");
            int niceValue = atoi(argv[2]);
            nice(niceValue);
        }else if (*argv[1]=='p'){
            printf("input char is p \n");
            int priotity = atoi(argv[2]);
            setpriority(PRIO_PROCESS, getpid(), priotity);

        }
    }

    pid_t pids[NUMOF_CHILDREN], pid;
    int i, n = NUMOF_CHILDREN;
    int retval;

    /* Start children */
    for(i=0;i<NUMOF_CHILDREN;i++) {
        pids[i] = fork();
        if (pids[i] < 0) {
            perror("fork");
            return 1;
        } else if (pids[i] == 0) {
            getProcessInformation();
            exit(0); /* the child process should EXIT and return 0 */
        }
    }

    /* Wait for children */
    while (n > 0) {
        pid = wait(&retval);
        printf("Parent: child with PID %ld exited with status 0x%x.\n", (long)pid, retval);
        --n;
    }

    return 0;
}   