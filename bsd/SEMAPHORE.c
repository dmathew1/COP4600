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
  pthread_mutex_init(&sem->mutex,NULL);
  pthread_cond_init(&np->condition,NULL);

  //sets the initialCount size for the semaphore
  sem->count = initialCount;

  //Initialize the semaphore's head as the queue
  SIMPLEQ_INIT(&(sem->conditionalQueue));


  //return the semaphore back
  return sem;
}

void cleanup_handler(void *sem1){
  semaphore_t *sem = (semaphore_t*) sem1;
  pthread_mutex_unlock(&sem->mutex);
}

//Destroys the semaphore
void destroySemaphore( semaphore_t* sem ){
  free(sem);
}

//Calls down on the semaphore whose purpose is to take a lock
void down( semaphore_t* sem ){
  struct entry *np;
  //mutual exclusion lock
  pthread_mutex_lock(&sem->mutex);
  //check if there are no more "locks" available
  if(sem->count<=0){
    ++sem->wakeupCount;


    //This is where I want to insert the conditional to the queue

    //create the new conditional object using the struct entry
    np = (struct entry *) malloc( sizeof( struct entry ) );
    SIMPLEQ_INSERT_TAIL( &sem->conditionalQueue, np, next );

    pthread_cleanup_push(cleanup_handler,sem);
    pthread_cond_wait(&np->condition,&sem->mutex);
    pthread_cleanup_pop(0);
  }

  --sem->count;

  //mutual exclusion unlock
  pthread_mutex_unlock(&sem->mutex);
}


//Calls up on the semaphore
//purpose is to release the lock
void up( semaphore_t* sem ){

    //mutual exclusion
    pthread_mutex_lock(&sem->mutex);
    if(sem->wakeupCount > 0 ){

      //This is where I want to dequeue from the SimpleQ
      SIMPLEQ_REMOVE_HEAD( &sem->conditionalQueue, (np = SIMPLEQ_FIRST(&sem->conditionalQueue)), next );
      pthread_cond_signal(&np->condition);
      free(np);
      --sem->wakeupCount;


    }
    ++sem->count;
    pthread_mutex_unlock(&sem->mutex);

}
