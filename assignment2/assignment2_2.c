#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>
#include <semaphore.h> 
#include <stdlib.h>

static sem_t obj_produced;
static sem_t obj_consumed;

static int shelf;

//Checks if the input number is prime (1) or not prime (0)
int checkPrime(int numberToCheck){
    int isPrime = 1, i;
    for (i=2;i<numberToCheck; i++) {
      if (numberToCheck % i ==0) {
        isPrime = 0;
      }
    }
    return isPrime;
}

//Provides numbers for the consumers to handle
void* producer() {
  int i;
  
  for(i=2; i< 10000; i++) {
    shelf = i;
    sem_post(&obj_produced);
    sem_wait(&obj_consumed);
  }

  return NULL;
}

// A consumer takes an object provided by the producer and checks if it is prime or not
void* consumer() { 
  // Store the value argument passed to this thread
  int numberToCheck;

  while(1) {
    sem_wait(&obj_produced);
    numberToCheck = shelf;
    sem_post(&obj_consumed);
    //printf("[CONSUMER] %d\n", numberToCheck);

    if(checkPrime(numberToCheck)==1) {
      printf(">>>> Thread %lu with PID %d announces that %d is prime.\n", pthread_self(), getpid(), numberToCheck);
    }
  }
}


int main() {
  int i = 0, err;
  pthread_t tid[5]; //5 threads: 1 producer and 4 consumers

  // create semaphores
  err = sem_init(&obj_produced, 0, 0);
  if(err != 0) {
    printf("Can't create semaphore: obj_produced [%s] \n", strerror(err));
    return 1;
  }
  err = sem_init(&obj_consumed, 0, 0);
  if(err != 0) {
    printf("Can't create semaphore: obj_produced [%s] \n", strerror(err));
    return 1;
  }

  // create producer thread
  err = pthread_create(&(tid[i]), NULL, &producer, NULL);
  if (err != 0) {
    printf("Can't create producer thread: [%s] \n", strerror(err));
    return 1;
  } 
  printf("Producer thread created\n");

  // create consumer threads
  for(i=1;i<5;i++) {
    err = pthread_create(&(tid[i]), NULL, &consumer, NULL);
    if (err != 0) {
      printf("Can't create consumer thread %d: [%s] \n", i, strerror(err));
    }
    printf("Consumer thread numer %d has been created\n", i);
  }

  // wait for producer thread
  pthread_join(tid[0], NULL);

  // kill consumer threads 
  for(i=1;i<5;i++) {
    pthread_kill(tid[i], 9);
  }

  // delete the semaphores
  sem_destroy(&obj_produced);
  sem_destroy(&obj_consumed);

  return 0;
}