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
  //sem->condition = PTHREAD_COND_INITIALIZER;
  pthread_cond_init(&sem->condition,NULL);

  //sets the initialCount size for the semaphore
  sem->count = initialCount;
  sem->totalCount = initialCount;

  //Initialize this dynamically as the semaphore's head to the queue
  //SIMPLEQ_INIT(&sem->head);
  return sem;
}

void cleanup_handler(void *sem1){
  semaphore_t *sem = (semaphore_t*) sem1;
  pthread_mutex_unlock(&sem->mutex);
}

//Destroys the semaphore
void destroySemaphore( semaphore_t* sem ){
  printf("In delete\n");
  fflush(stdout);
}

//Calls down on the semaphore
//purpose is to take a lock
void down( semaphore_t* sem ){
  //mutual exclusion lock
  pthread_mutex_lock(&sem->mutex);
  //check if there are no more "locks" available
  if(sem->count<=0){
    ++sem->wakeupCount;
    pthread_cleanup_push(cleanup_handler,sem);
    pthread_cond_wait(&sem->condition,&sem->mutex);
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
      pthread_cond_signal(&sem->condition);
      --sem->wakeupCount;
    }
    ++sem->count;
    pthread_mutex_unlock(&sem->mutex);

}
