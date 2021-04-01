#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h> 
#include <sys/resource.h>
#include <stdlib.h>

void heapOverflow(){
    for (int i=0; i<10000000000000; i++) {
      int *p = (int *)malloc(sizeof(int));
   }
}

void stackOverflow(int number){
    //Some basic logic
    if(number == 0) return;
    number = 9;
    //Recursion
    stackOverflow(number);
}

int main(void) {
    char input;
    printf("Do you want a Heap overflow or a Stack Overflof? (H/S)");
    scanf("%c",&input); 
    if (input == 'H' || input == 'h') {
        printf("Hold on, heap overflow will occur.");
        heapOverflow();
    }
    else if (input == 'S' || input == 's') {
        printf("Hold on, stack overflow will occur.");
        stackOverflow(2);
    }
    else {
        printf("No valid input, please try again.");
        main();
    }
    return 0;
}   