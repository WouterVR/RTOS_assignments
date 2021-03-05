#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int findPrime(int topNumber){
    int i;
    int amountOfPrimes = 0;
    pid_t pid = getpid();
    for(i=2; i<=topNumber; i++){ //looping throug all the numbers untill the highes number
        //printf("Checking the number: %d .\n", i);
        int j;
        int notPrime=0;
        for(j=2;j<=i/2;j++){ //Checking if prime or not
            //printf("Going to check %d percentage with %d . \n",i,j);
            if(i%j==0){
                notPrime=1;
                break;
            }
        }
        if(notPrime==0) {
            printf("child (PID= %d ) announces that %d is prime. \n",pid, i);
            amountOfPrimes++;
        }
    }
    printf("*** child process %d is ready and found that there are %d prime numbers under %d. *** \n",pid, amountOfPrimes, topNumber);
    return 0;
}

int main() {
    fork();
    fork();
    return findPrime(10000);
}