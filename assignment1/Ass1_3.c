#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int findPrime(int topNumber){
    int i;
    pid_t pid = getpid();
    for(i=1; i<=topNumber; ++i){ //looping throug all the numbers untill the highes number
        int j,m=0,flag=0;
        m=i/2;    
        for(j=2;j<=m;j++){ //Checking if prime or not
            if(i%j==0){     
                flag=1;
            }
        }
        if(flag==0) printf("child (PID= %d ) announces that %d is prime. \n",pid, i);     
        return 0;  
    }
}

int main() {
    fork();
    fork();
    return findPrime(10000);
}