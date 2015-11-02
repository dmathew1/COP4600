#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include "SEMAPHORE.H"


//Creates the semaphore
semaphore_t* createSemaphore( int initialCount ){
  semaphore_t t;
  t.count = initialCount;
  printf("test %d\n",t.count);

}

//Destroys the semaphore
void destroySemaphore( semaphore_t* sem ){
  printf("In delete\n");
}

//Calls down on the semaphore
void down( semaphore_t* sem ){

}

//Calls up on the semaphore
void up( semaphore_t* sem ){

}
