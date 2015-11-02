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
//purpose is to take a lock
void down( semaphore_t* sem ){
  //mutual exclusion lock
  //check if there are no more "locks" available
  //if there are no more locks
  //put calling thread in queue
  //else decrement counter
  //mutual exclusion unlock
}

//Calls up on the semaphore
//purpose is to release the lock
void up( semaphore_t* sem ){

}
