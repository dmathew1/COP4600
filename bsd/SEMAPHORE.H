#define SEMAPHORE_H
#include <sys/queue.h>

typedef struct{
  int count; //number of "locks" the semaphore can hand out
  pthread_mutex_t mutex; //the mutex lock
  pthread_cond_t condition; //the conditional variable
  //SIMPLEQ_HEAD(queuehead, entry) head; //lists this as the head of the simpleQ
  int wakeupCount;
  int totalCount;
}semaphore_t;


//Entries for the SIMPLEQ construct
/*typedef struct entry{
  SIMPLEQ_ENTRY(entry) next;
}*np;*/


//Create Semaphore function
semaphore_t* createSemaphore( int initialCount );

//Destroy Semaphore function
void destroySemaphore( semaphore_t* sem );

//Calling down on the semaphore function
void down( semaphore_t* sem );

//Calling up on the semaphore function
void up( semaphore_t* sem );

void cleanup_handler(void *sem1);
