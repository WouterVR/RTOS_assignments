#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
  
// A normal C function that is executed as a thread  
// when its name is specified in pthread_create() 
void* myThreadFun(void *vargp) { 
    sleep(1); 
    int threadID = -1;
    printf("Hello World from thread %d in process with process id: %d\n", threadID, getpid()); 
    return NULL; 
} 
   
int main() {
    pthread_t thread_id[2];
    int i=0;
    int possibleError;
    while(i<2){
        possibleError = pthread_create(&(thread_id[i]), NULL, &myThreadFun, NULL); 
        if(possibleError !=0) printf("Not able to create Thread:[%s]", strerror(possibleError));
        i++;
    }
    pthread_join(thread_id[0], NULL);
    pthread_join(thread_id[1], NULL);
    return(0); 
}