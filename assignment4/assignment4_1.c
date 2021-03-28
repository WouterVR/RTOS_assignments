#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h> 
#include <sys/resource.h>
#include <stdlib.h>

#define MAX_COUNT  5000
#define NUMOF_CHILDREN 12

int checkPrimes(){
    int numberToCheck = 0;
    int amountOfPrimes = 0;
    for(numberToCheck = 0; numberToCheck<MAX_COUNT; numberToCheck++){
        int isPrime = 1, i;
        for (i=2;i<numberToCheck; i++) {
            if (numberToCheck % i ==0) {
                isPrime = 0;
            }
        }
        if(isPrime) amountOfPrimes++;
    }
    intptr_t incrementHeapSize;
    sbrk(incrementHeapSize);
    printf("heap size:%p \n",sbrk(0) );
    printf("*** child process %d with a nice value of: %d is done looking for primes. It found: %d *** \n",getpid(), getpriority(PRIO_PROCESS, getpid()), amountOfPrimes);
    return 0;
}

int main(void) {
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
            int priority=0;
            // setting different priorities for the different processes
            // I chose to set the highest priorities for the processes that are created the last
            // In this way the influence of the priority number is more clear
            switch (i){
            case 0:
                priority = 19;
                break;
            case 1:
                priority = 17;
                break;
            case 2:
                priority = 15;
                break;
            case 3:
                priority = 10;
                break;
            case 4:
                priority = 7;
                break;
            case 5:
                priority = 5;
                break;
            case 6:
                priority = -0;
                break;
            case 7:
                priority = -5;
                break;
            case 8:
                priority = -7;
                break;
            case 9:
                priority = -10;
                break;
            case 10:
                priority = -15;
                break;
            case 11:
                priority = -19;
                break;
            
            default:
                priority = 0;
                break;
            }
            
            setpriority(PRIO_PROCESS, getpid(), priority);
            checkPrimes();
            exit(0); /* the child process should EXIT and return 0 */
        }
    }

    /* Wait for children */
    while (n > 0) {
        pid = wait(&retval);
        printf("Parent: child with PID %ld and exited with status 0x%x.\n", (long)pid, retval);
        --n;
    }

    return 0;
}   