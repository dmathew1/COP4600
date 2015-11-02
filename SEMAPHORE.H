
#define SEMAPHORE_H


typedef struct{
  int count;
  pthread_mutex_t lock;
  pthread_cond_t condition;
}semaphore_t;


semaphore_t* createSemaphore( int initialCount );

void destroySemaphore( semaphore_t* sem );

void down( semaphore_t* sem );

void up( semaphore_t* sem );
