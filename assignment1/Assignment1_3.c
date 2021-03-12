#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h> 

int findPrime(int topNumber){
    int i;
    int amountOfPrimes = 0;
    pid_t pid = getpid();
    for(i=2; i<=topNumber; i++){ //looping through all the numbers until the highest number
        int j;
        int notPrime=0;
        for(j=2;j<=i/2;j++){ //Checking if prime or not
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

    clock_t t; 
    t = clock();
	fork();
	fork();
	if(fork() == 0){ //for all the 4 child processes
		findPrime(10000);
	}

    t = clock() - t; 
    double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds 
    printf("It took %f seconds to execute this program", time_taken);
    return 0;
}