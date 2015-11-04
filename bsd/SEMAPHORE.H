#define SEMAPHORE_H
#include <sys/queue.h>

typedef struct{
  int count; //number of "locks" the semaphore can hand out
  pthread_mutex_t mutex; //the mutex lock
  //pthread_cond_t condition; //the conditional variable
  int wakeupCount; //variable that keeps track of how many blocked threads
  SIMPLEQ_HEAD(queuehead, entry) conditionalQueue; //SIMPLEQ that keeps track of the blocked threads
}semaphore_t;


//Entries for the SIMPLEQ construct
struct entry{
  pthread_cond_t condition;
  SIMPLEQ_ENTRY(entry) next;
}*np;


//Create Semaphore function
semaphore_t* createSemaphore( int initialCount );

//Destroy Semaphore function
void destroySemaphore( semaphore_t* sem );

//Calling down on the semaphore function
void down( semaphore_t* sem );

//Calling up on the semaphore function
void up( semaphore_t* sem );

//Clean up function
void cleanup_handler(void *sem1);
