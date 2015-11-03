#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include "SEMAPHORE.H"


//Creates the semaphore
semaphore_t* createSemaphore( int initialCount ){
  //creates a pointer to the semaphore
  semaphore_t* sem;

  //Allocates space on the memory address for the semaphore
  sem = (semaphore_t*)malloc(sizeof(semaphore_t));

  //Initialize mutex and condition variables
  sem->mutex = PTHREAD_MUTEX_INITIALIZER;
  sem->condition = PTHREAD_COND_INITIALIZER;

  //sets the initialCount size for the semaphore
  sem->count = initialCount;

  //Initialize this dynamically as the semaphore's head to the queue
  //SIMPLEQ_INIT(&sem->head);

  printf("test\n");
  return sem;
}

//Destroys the semaphore
void destroySemaphore( semaphore_t* sem ){
  printf("In delete\n");
}

//Calls down on the semaphore
//purpose is to take a lock
void down( semaphore_t* sem ){
  //mutual exclusion lock
  pthread_mutex_lock(&sem->mutex);

  //check if there are no more "locks" available
  if(sem->count==0){
    //if there are no more locks
    printf("Barber is waiting.\n");
    pthread_cond_wait(&sem->condition,&sem->mutex);
  }

    //There are locks
    --sem->count;

  //mutual exclusion unlock
  pthread_mutex_unlock(&sem->mutex);
}



//Calls up on the semaphore
//purpose is to release the lock
void up( semaphore_t* sem ){

    //mutual exclusion
    pthread_mutex_lock(&sem->mutex);
    ++sem->count;
    printf("Waking up any thread now\n");
    pthread_cond_signal(&sem->condition);
    pthread_mutex_unlock(&sem->mutex);

}
