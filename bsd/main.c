
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "SEMAPHORE.c"

#define BARBERS	5
#define CUSTOMERS 5
#define CHAIRS 5

semaphore_t *barberSem;
semaphore_t *customerSem;
semaphore_t *mutex;
int waiting = 0;


void * receive_cut(){
  printf("Nigga got his haircut\n");
}

void * cut_hair(){
  printf("Nigga is getting the haircut\n");
}

void * barber()
{
  while(1){
    down(customerSem);
    down(mutex);
    --waiting;
    up(barberSem);
    up(mutex);
    cut_hair();
  }
}

void * customer(){
  down(mutex);
  if(waiting < CHAIRS){
    ++waiting;
    up(customerSem);
    up(mutex);
    down(barberSem);
    receive_cut();
    pthread_exit(NULL);
  }
}


int main( void )
{
  int i;
  pthread_t barberThreads[BARBERS];
  pthread_t customerThreads[CUSTOMERS];

  barberSem = createSemaphore(5);
  customerSem = createSemaphore(5);
  mutex = createSemaphore(1);


  for ( i = 0; i < BARBERS; ++i )
  {

    // make the threads
    if( pthread_create( &barberThreads[i], NULL, barber, NULL) )
    {
      printf( "ERROR: creating thread %d\n", i );
      exit(-1);
    }
    else
    {
      printf( "Created barber %d\n", i );
    }
  }

  // wait for the threads to terminate
  for ( i = 0; i < BARBERS; ++i )
  {
    if ( pthread_cancel( barberThreads[i] ) )
    {
      printf("ERROR: joining thread %d\n", i );
    }
    else
    {
      printf("Joined barber %d\n", i );
    }
  }


  for ( i = 0; i < CUSTOMERS; ++i )
  {

    // make the threads
    if( pthread_create( &customerThreads[i], NULL, customer, NULL) )
    {
      printf( "ERROR: creating thread %d\n", i );
      exit(-1);
    }
    else
    {
      printf( "Created customer %d\n", i );
    }
  }

  // wait for the threads to terminate
  for ( i = 0; i < CUSTOMERS; ++i )
  {
    if ( pthread_join( customerThreads[i], NULL ) )
    {
      printf("ERROR: joining thread %d\n", i );
    }
    else
    {
      printf("Joined customer %d\n", i );
    }
  }



  pthread_exit(NULL);
}
